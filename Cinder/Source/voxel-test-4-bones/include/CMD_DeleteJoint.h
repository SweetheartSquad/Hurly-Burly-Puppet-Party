#pragma once

#include <vector>

#include "Command.h"

class Node;
class NodeHierarchical;
class Joint;

class CMD_DeleteJoint : public Command{
public:
	CMD_DeleteJoint(std::vector<Joint *> * joints);
	~CMD_DeleteJoint(void);

	void execute();
	void unexecute();

private:
	std::vector<Joint *> * joints;

	// The joints which this command is in reference to
	std::vector<Node *> jointsForDeletion;
	
	// Location in jointForDeletion's parent's list of children (or the joint list if it was a root) at which jointForDeletion exists
	std::vector<unsigned long int> index;

	// If jointForDeletion had children, a copy of them are stored here
	std::vector<std::vector<NodeHierarchical *>> children;
	
	// False on creation, true after call to execute, false after call to unexecute
	bool executed;
};