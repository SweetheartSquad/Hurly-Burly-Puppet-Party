#pragma once 

#include <shader\ShaderComponent.h>

class ShaderComponentTint : public ShaderComponent{
private:
	float red, green, blue;
public:
	float getRed();
	float getGreen();
	float getBlue();
	void setRed(float _r);
	void setGreen(float _g);
	void setBlue(float _b);

	// all values are given as 0 - 1, h += hue, s *= sat, v *= val, a *= alpha
	ShaderComponentTint(Shader * _shader, float _r, float _g, float _b);
	~ShaderComponentTint();
	
	std::string getVertexVariablesString() override;
	std::string getFragmentVariablesString() override;
	std::string getVertexBodyString() override;
	std::string getFragmentBodyString() override;
	std::string getOutColorMod() override;
	void configureUniforms(vox::MatrixStack* _matrixStack, RenderOptions* _renderOption, NodeRenderable* _nodeRenderable) override;
};