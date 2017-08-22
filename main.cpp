#include <Windows.h>
#include <assert.h>
#include <iostream>


struct TreeNode
{
	TreeNode* mParent = nullptr;
	TreeNode* mFirchChild = nullptr;
	TreeNode* mDown = nullptr;

	//calculates the leaf index, aka the index from parent to this child
	unsigned GetLeafIndex() const
	{
		unsigned index = 0;
		auto parent = mParent;
		while (parent)
		{
			index++;
			parent = parent->mParent;
		}
		return index;
	}
	TreeNode(TreeNode* parent = nullptr)
	{
		mParent = parent;
		if (parent)
		{
			mDown = parent->mFirchChild;
			mParent->mFirchChild = this;
		}
	}
	//calls @proc only on each child of this node
	template<typename TLambda> void ForEachChild(TLambda proc)
	{
		auto child = mFirchChild;
		while (child)
		{
			proc(child);
			child = child->mDown;
		}
	}
	//calls @proc on children of this node and their sub-children recursively
	template<typename TLambda> void ForEachChildRec(TLambda proc)
	{
		auto child = mFirchChild;
		while (child)
		{
			proc(child);
			child->ForEachChildRec(proc);
			child = child->mDown;
		}
	}
	//calls @proc on the children and sub children continuously in the same leaf index
	template<typename TLambda> void ForEachChildChild(TLambda proc)
	{
		auto* child = mFirchChild;
		while (child)
		{
			proc(child);
			child = child->mDown;
		}

		child = mFirchChild;
		while (child)
		{
			child->ForEachChildChild(proc);
			child = child->mDown;
		}
	}
};

TreeNode* TestMakeTree()
{
	auto root = new TreeNode(nullptr);

	{
		auto aa = new TreeNode(root);
		{
			auto bb = new TreeNode(aa);
			{
				auto dd = new TreeNode(bb);
				{
					auto ff = new TreeNode(dd);
					{
						new TreeNode(ff);
						new TreeNode(ff);
						new TreeNode(ff);
						new TreeNode(ff);
						new TreeNode(ff);
						new TreeNode(ff);
					}
					auto gg = new TreeNode(dd);
				}
				auto ee = new TreeNode(bb);
				{
					auto ff = new TreeNode(ee);
					auto gg = new TreeNode(ee);
				}
			}
			new TreeNode(aa);
			new TreeNode(aa);
			new TreeNode(aa);
		}
	}
	return root;
}


int main()
{
	TreeNode* tree = TestMakeTree();

	std::cout << "=======================\n";
	tree->ForEachChildRec([](TreeNode* node) {
		std::cout << node->GetLeafIndex() << '\n';
	});

	std::cout << "=======================\n";
	tree->ForEachChildChild([](TreeNode* node) {
		std::cout << node->GetLeafIndex() << '\n';
	});

	int nn = 0;
	std::cin >> nn;
    return 0;
}

