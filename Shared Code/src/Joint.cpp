#pragma once

#include <cinder\app\App.h>

#include "Joint.h"
#include "Transform.h"

#include "MatrixStack.h"
#include "RenderOptions.h"

unsigned long int Joint::nextId = 0;

void Joint::deleteJoints(NodeHierarchical * _j){
	for(unsigned long int i = 0; i < _j->children.size(); ++i){
		deleteJoints(_j->children.at(i));
	}
	delete _j;
}

void Joint::init(){
	depth = 0;
	parent = nullptr;
	id = nextId;
	nextId += 1;
	shader = nullptr;
}

Joint::Joint() : 
	NodeAnimatable(new Transform()),
	NodeHierarchical(nullptr),
	NodeSelectable()
{
	init();
}

Joint::Joint(NodeHierarchical * _parent) : 
	//NodeTransformable(new Transform()),
	NodeAnimatable(new Transform()),
	NodeHierarchical(_parent),
	NodeSelectable()
{
	init();
	parent = _parent;
	while(_parent != nullptr){
		_parent = _parent->parent;
		depth += 1;
	}
}

void Joint::setPos(Vec3d _pos, bool _convertToRelative){
	glm::vec4 newPos(_pos.x, _pos.y, _pos.z, 1);
	if(_convertToRelative){
		NodeHierarchical * _parent = parent;
		std::vector<glm::mat4> modelMatrixStack;
		while(_parent != nullptr){
			modelMatrixStack.push_back(dynamic_cast<NodeTransformable *>(_parent)->transform->getModelMatrix());
			_parent = _parent->parent;
		}

		glm::mat4 modelMatrix(1);
		for(unsigned long int i = modelMatrixStack.size(); i > 0; --i){
			modelMatrix = modelMatrix * modelMatrixStack.at(i-1);
		}
		newPos = glm::inverse(modelMatrix) * newPos;
	}
	transform->translationVector = glm::vec3(newPos.x, newPos.y, newPos.z);
}

Vec3d Joint::getPos(bool _relative){
	glm::vec4 res(transform->translationVector.x, transform->translationVector.y, transform->translationVector.z, 1);
	if(!_relative){
		NodeHierarchical * _parent = parent;
		std::vector<glm::mat4> modelMatrixStack;
		while(_parent != nullptr){
			modelMatrixStack.push_back(dynamic_cast<NodeTransformable *>(_parent)->transform->getModelMatrix());
			_parent = _parent->parent;
		}
		
		glm::mat4 modelMatrix(1);
		for(unsigned long int i = modelMatrixStack.size(); i > 0; --i){
			modelMatrix = modelMatrix * modelMatrixStack.at(i-1);
		}
		res = modelMatrix * res;
	}
	return Vec3d(res.x, res.y, res.z);
}

Joint::~Joint(){
	delete transform;
}

void Joint::render(MatrixStack * _matrixStack, RenderOptions * _renderStack){
	if(shader != nullptr){
		//gl::enableWireframe();
		shader->uniform("pickingColor", Color::hex(pickingColor));
		//colour
		if(depth%3 == 0){
			gl::color(0, 1, 1);
		}else if(depth%3 == 1){
			gl::color(1, 0, 1);
		}else{
			gl::color(1, 1, 0);
		}

		//draw joint
		gl::pushModelView();
		_matrixStack->pushMatrix();
			gl::translate(transform->translationVector.x,
								transform->translationVector.y,
								transform->translationVector.z);
			//vox::translate(transform->getModelMatrix());

			//gl::pushMatrices(); 
			//gl::popMatrices();
	
			gl::rotate(Quatd(transform->orientation.w,
								transform->orientation.x,
								transform->orientation.y,
								transform->orientation.z));

			gl::scale(transform->scaleVector.x, transform->scaleVector.y, transform->scaleVector.z);
			//vox::rotate(transform->getOrientationMatrix());
			_matrixStack->applyMatrix(transform->getModelMatrix());

			glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &_matrixStack->currentModelMatrix[0][0]);
			gl::drawSphere(Vec3f(0.f, 0.f, 0.f), 0.05f);

			//draw voxels
			for(unsigned long int i = 0; i < voxels.size(); ++i){
				gl::pushModelView();
				_matrixStack->pushMatrix();
					gl::translate(voxels.at(i)->pos);
					Transform t;
					t.translate(voxels.at(i)->pos.x, voxels.at(i)->pos.y, voxels.at(i)->pos.z);
					_matrixStack->translate(t.getTranslationMatrix());
			
					glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &_matrixStack->currentModelMatrix[0][0]);
					shader->uniform("pickingColor", Color::hex(voxels.at(i)->pickingColor));
					gl::drawSphere(Vec3f(0.f, 0.f, 0.f), 0.06f, 16);
				gl::popModelView();
				_matrixStack->popMatrix();
			}
		
			shader->uniform("pickingColor", Color::hex(pickingColor));
			//draw bones
			for(NodeHierarchical * child : children){
				Vec3d cinderTrans(
					dynamic_cast<NodeTransformable *>(child)->transform->translationVector.x,
					dynamic_cast<NodeTransformable *>(child)->transform->translationVector.y,
					dynamic_cast<NodeTransformable *>(child)->transform->translationVector.z
				);
				Quatd boneDir(Vec3d(0.0, 1.0, 0.0), cinderTrans);
				gl::pushMatrices();
				_matrixStack->pushMatrix();
					gl::rotate(boneDir);
					Transform temp;
					temp.orientation.x = boneDir.v.x;
					temp.orientation.y = boneDir.v.y;
					temp.orientation.z = boneDir.v.z;
					temp.orientation.w = boneDir.w;
					_matrixStack->rotate(temp.getOrientationMatrix());
			
					glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &_matrixStack->currentModelMatrix[0][0]);
					gl::drawSolidTriangle(Vec2f(0.05f, 0.f), Vec2f(-0.05f, 0.f), Vec2f(0.f, cinderTrans.length()));

					gl::rotate(Vec3f(0.f, 90.f, 0.f));
					Transform temp2;
					temp2.rotate(90, 0, 1, 0);
					_matrixStack->rotate(temp2.getOrientationMatrix());
			
					glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, &_matrixStack->currentModelMatrix[0][0]);
					gl::drawSolidTriangle(Vec2f(0.05f, 0.f), Vec2f(-0.05f, 0.f), Vec2f(0.f, cinderTrans.length()));
				gl::popMatrices();
				_matrixStack->popMatrix();

				dynamic_cast<Joint *>(child)->shader = shader;
				dynamic_cast<Joint *>(child)->render(_matrixStack, _renderStack);
			}
		gl::popModelView();
		_matrixStack->popMatrix();

		//gl::disableWireframe();
	}else{
		throw "no shader attached";
	}
}