class Node{
    int data;
    Node left, right;
    public Node(int value){
        data = value;
        left = rigt = null;
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

