import java.util.Scanner;

class Node {
    int data;
    Node left, right;
    int height;

    public Node(int value) {
        data = value;
        //initialise to null pointers
        left = right = null;
        height = 1;
    }
}

//class which holds methods to traverse the tree
class Traversals {

    static void printCurrentLevel(Node root, int level)
    {
        if (root == null)
            return;
        if (level == 1)
            System.out.print(root.data + " ");
        else if (level > 1) {
            printCurrentLevel(root.left, level - 1);
            printCurrentLevel(root.right, level - 1);
        }
    }
    static void levelorder(Node node)
    {
        if(node == null)
        {
            return;
        }
        for(int i = 1; i <= node.height; i++)
        {
            printCurrentLevel(node, i);

        }
        

    }
    static void inorder(Node node) {
        if (node == null) {
            return;
        }

        inorder(node.left); // go down left subtree
        System.out.print(node.data + " "); // print data
        inorder(node.right);// go down right subtree
    }

    static void preorder(Node node) {
        if (node == null) {
            return;
        }

        System.out.print(node.data + " ");
        preorder(node.left); // go down left subtree
        preorder(node.right); // go down right subtree
    }

    static void postorder(Node node) {
        if (node == null) {
            return;
        }

        postorder(node.left);
        postorder(node.right);
        System.out.print(node.data + " ");
    }
}

class AVL {

    // utility function to get the height of the tree
    static int height(Node node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }

    static Node Rotate_Right(Node y) {
        Node x = y.left;
        Node store_right = x.right;

        // performing rotation
        x.right = y;
        y.left = store_right;

        // updating heights
        y.height = 1 + Math.max(height(y.left), height(y.right));
        x.height = 1 + Math.max(height(x.left), height(x.right));

        // returning new root
        return x;
    }

    static Node Rotate_Left(Node x) {
        Node y = x.right;
        Node store_left = y.left;

        // performing rotation
        y.left = x;
        x.right = store_left;

        // upadating heights
        x.height = 1 + Math.max(height(x.left), height(x.right));
        y.height = 1 + Math.max(height(y.left), height(y.right));

        //returning new roots
        return y;
    }

    
    static int getBalance(Node node) {
        if (node == null) {
            return 0;
        }
        int balance = height(node.left) - height(node.right);
        return balance;
    }

    static Node minValueNode(Node node)
    {
        Node current = node;

        //loop down to find
        while(current.left != null)
        {
            current = current.left;
        }
        return current;
    }

    static Node insert(Node node, int data) {
        // perform the normal bst insertion
        if (node == null) {
            return new Node(data);
        }

        // inserting on left node
        if (data < node.data) {
            node.left = insert(node.left, data);
        }
        // inserting on right node
        else if (data > node.data) {
            node.right = insert(node.right, data);
        }
        // equal keys not allowed in bst
        else {
            return node;
        }
        // update height of ancestor node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // get the balance factor of this ancestor node
        int balance = getBalance(node);

        // if this node becomes unbalanced, then check 4 cases

        // left left
        if (balance > 1 && data < node.left.data) {
            return Rotate_Right(node);
        }

        // right right
        if (balance < -1 && data > node.right.data) {
            return Rotate_Left(node);

        }

        // left right
        if (balance > 1 && data > node.left.data) {
            node.left = Rotate_Left(node.left);
            return Rotate_Right(node);
        }

        // right left
        if (balance < -1 && data < node.right.data) {
            node.right = Rotate_Right(node.right);
            return Rotate_Left(node);
        }

        // returning unchanged node pointer if no cases met
        return node;
    }

    static Node delete(Node root, int data) {
        // standard null case
        if (root == null) {
            return root;
        }

        // data lies in left subtree
        if (data < root.data) {
            root.left = delete(root.left, data);
        }

        // data lies in right subtree
        else if (data > root.data) {
            root.right = delete(root.right, data);
        }
        // data is here
        else {
            // node with only one child or no child
            if ((root.left == null) || (root.right == null)) {
                Node temp = root.left != null ? root.left : root.right;

                // no child case
                if (temp == null) {
                    temp = root;
                    root = null;
                }
                // one child case
                else {
                    // copy the contents of the non-empty child
                    root = temp;
                }
            } else {
                // node with two kids
                // get smallest in right subtree
                Node temp = minValueNode(root.right);

                // copy the kid
                root.data = temp.data;

                // delete the kid
                root.right = delete(root.right, temp.data);
            }
            if(root == null)
            {
                return root;
            }

        }

        // update the height of the current node
        root.height = Math.max(height(root.left), height(root.right)) + 1;

        // get balance factor of the node
        int balance = getBalance(root);
        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root.left) >= 0)
            return Rotate_Right(root);

        // Left Right Case
        if (balance > 1 && getBalance(root.left) < 0) {
            root.left = Rotate_Left(root.left);
            return Rotate_Right(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root.right) <= 0)
            return Rotate_Left(root);

        // Right Left Case
        if (balance < -1 && getBalance(root.right) > 0) {
            root.right = Rotate_Right(root.right);
            return Rotate_Left(root);
        }
        return root;

    }
}

//fun task to do if i find time, see if i can cut down how much code i have
public class main {
    public static void main(String[] args) {

        //scan for input
        Scanner scanner = new Scanner(System.in);
        String inputString = scanner.nextLine();
        scanner.close();

        //splitting with space as the delim
        String[] instructions = inputString.split(" ");

        Node root = null;

        for(int i = 0; i < instructions.length -1; i++)
        {
            //rename this variable
            String dickNUTS = instructions[i];
            //breaking up the operation and value
            char operation = dickNUTS.charAt(0);
            int value = Integer.parseInt(dickNUTS.substring(1));

            if(operation == 'A')
            {
                root = AVL.insert(root, value);
            }
            else if (operation == 'D')
            {
                root = AVL.delete(root, value);
            }

        }
        String final_instruction = instructions[instructions.length - 1];
        if(final_instruction.equals("PRE"))
        {
            if(root == null)
            {
                System.out.println("EMPTY");
            }
            else
            {
                Traversals.preorder(root);
                System.out.println();

            }

        }

        else if(final_instruction.equals("POST"))
        {
            if(root == null)
            {
                System.out.println("EMPTY");
            }
            else
            {
                Traversals.postorder(root);
                System.out.println();

            }

        }
        else if(final_instruction.equals("IN"))
        {
            if(root == null)
            {
                System.out.println("EMPTY");
            }
            else
            {
                Traversals.inorder(root);
                System.out.println();

            }

        }
        else if(final_instruction.equals("LVL"))
        {
            if(root == null)
            {
                System.out.println("EMPTY");
            }
            else
            {
                Traversals.levelorder(root);
                System.out.println();

            }

        }


    }
}
