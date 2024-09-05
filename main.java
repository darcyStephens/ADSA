class Node{
    int data;
    Node left, right;
    int height;
    public Node(int value){
        data = value;
        left = right = null;
        height = 1;
    }
}

class Traversals{
    static void inorder(Node node) {
        if(node == null)
        {
            return;
        }

      
        inorder(node.left);  //go down left subtree
        System.out.print(node.data + " "); //print data
        inorder(node.right);//go down right subtree
    }
    static void preorder(Node node){
        if(node == null)
        {
            return;
        }

        System.out.print(node.data + " ");
        preorder(node.left); //go down left subtree
        preorder(node.right); //go down right subtree
    }

    static void postorder(Node node)
    {
        if(node == null)
        {
            return;
        }

        postorder(node.left);
        postorder(node.right);
        System.out.print(node.data + " ");
    }
}

class AVL {
    //utility function to get the height of the tree
    static int height(Node node)
    {
        if (node == null)
        {
            return 0;
        }
        return node.height;
    }

    static Node Rotate_Right(Node y)
    {
        Node x = y.left;
        Node T2 = x.right;

        //perform rotation
        x.right = y;
        y.left = T2;

        //updating heights
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));

        //return new root
        return x;
    }

    static Node Rotate_Left(Node x)
    {
        Node y = x.right;
        Node T2 = y.left;

        //perform rotation
        y.left = x;
        x.right = T2;

        //upadate heights
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));

        return x;
    }

    static int getBalance(Node node)
    {
        if(node == null)
        {
            return 0;
        }
        int balance = height(node.left) - height(node.right);
        return balance;
    }

    static Node insert(Node node, int data)
    {
        //perform the normal bst insertion
        if(node == null)
        {
            return new Node(data);
        }

        //inserting on left node
        if(data < node.data)
        {
            node.left = insert(node.left, data);
        }
        //inserting on right node
        else if(data > node.data)
        {
            node.right = insert(node.right, data);
        }
        //equal keys not allowed in bst
        else
        {
            return node;
        }
        //update height of ancestor node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        //get the balance factor of this ancestor node
        int balance = getBalance(node);

        //if this node becomes unbalanced, then check 4 cases

        //left left
        if(balance > 1 && data < node.left.data)
        {
            return Rotate_Right(node);
        }

        //right right
        if(balance < -1 && data > node.right.data)
        {
            return Rotate_Left(node);

        }

        //left right
        if(balance > 1 && data > node.left.data)
        {
            node.left = Rotate_Left(node.left);
            return Rotate_Right(node);
        }

        //right left
        if(balance < -1 && data < node.right.data)
        {
            node.right = Rotate_Right(node.right);
            return Rotate_Left(node);
        }
        
        //returning unchanged node pointer if no cases met
        return node;
    }
}
