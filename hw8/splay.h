#include "Map.h"
#include "bst.h"

class Splay : public Map, BinarySearchTree<std::string, int>
{
public:
	Splay() : count(0) {}
	~Splay() {}

	void add(const std::string& word)
	{
		Node<std::string, int> * curr;
		const std::string newWord = convertToLower(word);
		curr = this->internalFind(newWord);
		if(curr) curr->setValue(curr->getValue()+1); // increment
		else
		{	// couldn't find item.
			insert(std::make_pair(newWord, 1));
			curr = this->internalFind(newWord);
			count++;
		}

		splay(curr);
	}

	void reportAll(std::ostream& output)
	{	// print everything in new lines
		for(Splay::iterator it = this->begin(); it != this->end(); ++it)
			output << it->first << " " << it->second << std::endl;
		std::cout << "Count: " << count << std::endl;
	}

private:
	unsigned int count;

	const std::string convertToLower(const std::string & string) const
	{
		std::string word = string;
		for(unsigned int i=0; i < word.length(); i++)
			if(word[i] >= 'A' && word[i] <= 'Z')
				word[i] += 32;
		return word;
	}

	void splay(Node<std::string, int> * item)
	{
		while(item->getParent())
		{
			if(!item->getParent()->getParent())
			{ // i c u root :)
				if(item->getParent()->getLeft() == item) zig(item->getParent());
				else zag(item->getParent());
			}
			else if(item->getParent()->getLeft() == item && item->getParent()->getParent()->getLeft() == item->getParent())
			{ // zig zig
				zig(item->getParent()->getParent());
				zig(item->getParent());
			}
			else if(item->getParent()->getRight() == item && item->getParent()->getParent()->getRight() == item->getParent())
			{ // zag zag
				zag(item->getParent()->getParent());
				zag(item->getParent());
			}
			else if(item->getParent()->getLeft() == item && item->getParent()->getParent()->getRight() == item->getParent())
			{ // zag zig
				zig(item->getParent());
				zag(item->getParent());
			}
			else
			{ // zig zag
				zag(item->getParent());
				zig(item->getParent());
			}

		}
	}

    // RIGHT_ROTATE
    Node<std::string, int> * zig (Node<std::string, int> * nodeA)
    {
        Node<std::string, int> * nodeB = nodeA->getLeft();
        if(!nodeB) return nodeA; // secondary node doesn't exist, can't rotate

        if(nodeA->getParent()) // set parent
        {
            if(nodeA == nodeA->getParent()->getLeft())
                nodeA->getParent()->setLeft(nodeB);
            else nodeA->getParent()->setRight(nodeB);
        }
        else // might be root?
            if(nodeA == this->root)
                this->root = nodeB;
        nodeB->setParent(nodeA->getParent());

        // reattach
        nodeA->setLeft(nodeB->getRight());
        if(nodeB->getRight()) nodeB->getRight()->setParent(nodeA);
        nodeB->setRight(nodeA);
        nodeA->setParent(nodeB);
        return nodeB;
    }
    // LEFT_ROTATE
    Node<std::string, int> * zag (Node<std::string, int> * nodeA)
    {
        Node<std::string, int> * nodeB = nodeA->getRight();
        if(!nodeB) return nodeA; // secondary node doesn't exist, can't rotate

        if(nodeA->getParent()) // set parent
        {
            if(nodeA == nodeA->getParent()->getLeft())
                nodeA->getParent()->setLeft(nodeB);
            else nodeA->getParent()->setRight(nodeB);
        }
        else // might be root?
        	if(nodeA == this->root)
                this->root = nodeB;
        nodeB->setParent(nodeA->getParent());

        // reattach
        nodeA->setRight(nodeB->getLeft());
        if(nodeB->getLeft()) nodeB->getLeft()->setParent(nodeA);
        nodeB->setLeft(nodeA);
        nodeA->setParent(nodeB);
        return nodeB;
    }
};
