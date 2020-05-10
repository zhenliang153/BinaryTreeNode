#include <iostream>
#include <memory>
#include <vector>

/*
 * 图解层序遍历和逐层打印二叉树
 * Reproduce from cnblogs 2019-06-14
 * https://www.cnblogs.com/apocelipes/p/10758692.html
 */

class BinaryTreeNode: public std::enable_shared_from_this<BinaryTreeNode>
{
public:
	explicit BinaryTreeNode(const int value = 0):
		_value{value}, 
		_left{std::shared_ptr<BinaryTreeNode>{}},
		_right{std::shared_ptr<BinaryTreeNode>{}}
	{}

	void insert(int value);
	void ldr();
	void layer_print();

private:
	std::vector<std::shared_ptr<BinaryTreeNode>> layer_contents();

private:
	int _value;
	std::shared_ptr<BinaryTreeNode> _left;
	std::shared_ptr<BinaryTreeNode> _right;
};


void BinaryTreeNode::insert(int value)
{
	if(value < _value)
	{
		if(_left != nullptr)
			_left->insert(value);
		else
			_left = std::make_shared<BinaryTreeNode>(value);
	}
	else if(value > _value)
	{
		if(_right != nullptr)
			_right->insert(value);
		else
			_right = std::make_shared<BinaryTreeNode>(value);
	}
}

//中序遍历
void BinaryTreeNode::ldr()
{
	if(_left != nullptr)
		_left->ldr();

	std::cout << _value << std::endl;

	if(_right != nullptr)
		_right->ldr();
}

void BinaryTreeNode::layer_print()
{
	auto nodes = layer_contents();
	for(auto iter = nodes.begin(); iter != nodes.end(); ++iter)
	{
		if(*iter)
			std::cout << (*iter)->_value << " ";
			//std::cout << (*iter)->_value << std::endl;
		else
			std::cout << std::endl;
	}
}

//层序添加，层与层之间用nullptr隔开
std::vector<std::shared_ptr<BinaryTreeNode>> BinaryTreeNode::layer_contents()
{
	std::vector<std::shared_ptr<BinaryTreeNode>> nodes;
	nodes.push_back(shared_from_this());
	nodes.push_back(nullptr);

	for(int index = 0; index < nodes.size(); ++index)
	{
		std::cout << "nodes.size() == " << nodes.size() << std::endl;
		if(!nodes.at(index))
		{
			if(index == nodes.size() - 1)
				break;
			nodes.push_back(nullptr);
			continue;
		}

		if(nodes.at(index)->_left)
			nodes.push_back(nodes.at(index)->_left);

		if(nodes.at(index)->_right)
			nodes.push_back(nodes.at(index)->_right);
	}

	return nodes;
}

int main()
{
	auto root = std::make_shared<BinaryTreeNode>(3);
	root->insert(1);
	root->insert(0);
	root->insert(2);
	root->insert(5);
	root->insert(4);
	root->insert(6);
	root->insert(7);
	root->ldr();

	std::cout << std::endl;
	root->layer_print();

	return 0;
}
