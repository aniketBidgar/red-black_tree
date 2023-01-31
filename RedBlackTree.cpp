#include <iostream>
using namespace std;

struct RbTreeNode{
    int value;
    char colour;
    RbTreeNode *parent, *leftChild, *rightChild;
}*root=NULL;

void rotateTreeLeft(RbTreeNode *rotateNode)
{
     if(rotateNode->rightChild!=NULL){
           RbTreeNode *temp=rotateNode->rightChild;
           if(temp->leftChild!=NULL){
                rotateNode->rightChild=temp->leftChild;
                temp->leftChild->parent=rotateNode;
           }else{
			   rotateNode->rightChild=NULL;
		   }
                  
           if(rotateNode->parent!=NULL){
			   temp->parent=rotateNode->parent;
		   } 
           if(rotateNode->parent==NULL){
			   root=temp;
		   }else{
               if(rotateNode==rotateNode->parent->leftChild){
				   rotateNode->parent->leftChild=temp;
			   }else{
				   rotateNode->parent->rightChild=temp;
			   }      
           }
           temp->leftChild=rotateNode;
           rotateNode->parent=temp;
     }else{
         return;
     }
}
void rotateTreeRight(RbTreeNode *rotateNode)
{
     if(rotateNode->leftChild!=NULL) {
         RbTreeNode *temp=rotateNode->leftChild;
         if(temp->rightChild!=NULL){
            rotateNode->leftChild=temp->rightChild;
            temp->rightChild->parent=rotateNode;
         }else{
			rotateNode->leftChild=NULL; 
		 }
         if(rotateNode->parent!=NULL){
			temp->parent=rotateNode->parent; 
		 }
		 if(rotateNode->parent==NULL){
			root=temp; 
		 }else{
             if(rotateNode==rotateNode->parent->leftChild){
				rotateNode->parent->leftChild=temp; 
			 }else{
				rotateNode->parent->rightChild=temp; 
			 }     
         }
         temp->rightChild=rotateNode;
         rotateNode->parent=temp;
     }else{
        return;
     }
}

void insertNodeFix(RbTreeNode *inputNode)
{
     RbTreeNode *uncleNode;
     if(root==inputNode)
     {
         inputNode->colour='B';
         return;
     }
     while(inputNode->parent!=NULL&&inputNode->parent->colour=='R')
     {
        RbTreeNode *grandfatherNode = inputNode->parent->parent;
        if(grandfatherNode->leftChild==inputNode->parent){
            if(grandfatherNode->rightChild!=NULL){
                uncleNode=grandfatherNode->rightChild;
                if(uncleNode->colour=='R'){
                    inputNode->parent->colour='R';
                    uncleNode->colour='B';
                    grandfatherNode->colour='B';
                    inputNode=grandfatherNode;
                }
            }else{
                if(inputNode->parent->rightChild==inputNode){
                    inputNode=inputNode->parent;
                    rotateTreeLeft(inputNode);
                }
                inputNode->parent->colour='B';
                grandfatherNode->colour='R';
                rotateTreeRight(grandfatherNode);
            }
        }else{
            if(grandfatherNode->leftChild!=NULL){
                uncleNode=grandfatherNode->leftChild;
                if(uncleNode->colour=='R'){
                    inputNode->parent->colour='B';
                    uncleNode->colour='B';
                    grandfatherNode->colour='R';
                    inputNode=grandfatherNode;
                }
            }else{
                if(inputNode->parent->leftChild==inputNode){
                    inputNode=inputNode->parent;
                    rotateTreeRight(inputNode);
                }
                inputNode ->parent->colour='B';
                grandfatherNode->colour='R';
                rotateTreeLeft(grandfatherNode);
            }
        }
        root->colour='B';
    }
}

void insertNode(int input){
    RbTreeNode *newNode = new RbTreeNode;
    newNode->value = input;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->colour = 'R';
    RbTreeNode *temp, *tempChild;
    
    tempChild = NULL;
    if(root==NULL){//root node is empty insert new node as root node
        root = newNode;
        newNode->parent = NULL;
    }else{//root node is not empty
        temp = root;
        while(temp!=NULL){
            tempChild = temp;
            if(temp->value<newNode->value){
                temp = temp->rightChild;
            }else{
                temp = temp->leftChild;
            }
        } 
        newNode->parent = tempChild;
        if(tempChild->value<newNode->value){
                tempChild->rightChild = newNode;
            }else{
                tempChild->leftChild = newNode;
            }
    }
    insertNodeFix(newNode);
}

void displayTreeElements(RbTreeNode *tree)
{
    if (tree != NULL)
    {
        displayTreeElements(tree->leftChild);
        cout<<tree->value<<tree->colour<<"\t";
        displayTreeElements(tree->rightChild);
    }
} 

void searchElement(int searchInput)
{
    if(root!=NULL){
        RbTreeNode *temp=root;
        int flag = 0;
        while(temp!=NULL&& flag==0){
            if(temp->value==searchInput){
                flag++;
            }
            if(flag==0){
                if(temp->value<searchInput){
                   temp=temp->rightChild; 
                }else{
                   temp=temp->leftChild; 
                }
            }
        }
        if(flag==0){
           cout<<"\nABSENT\n";
        }else{
           cout<<"PRESENT\n";
        } 
    }else{
        cout<<"EMPTY\n";
    }
     
}

void deleteNodeFix(RbTreeNode *inputNode)
{
    RbTreeNode *siblingNode;
    while(inputNode!=root && inputNode->colour=='B')
    {
          if(inputNode->parent->leftChild==inputNode){
                  siblingNode=inputNode->parent->rightChild;
                  if(siblingNode->colour=='R'){
                         siblingNode->colour='B';
                         inputNode->parent->colour='R';
                         rotateTreeLeft(inputNode->parent);
                         siblingNode=inputNode->parent->rightChild;
                  }if(siblingNode->rightChild->colour=='B' && siblingNode->leftChild->colour=='B'){
                         siblingNode->colour='R';
                         inputNode=inputNode->parent;
                  }else{
                      if(siblingNode->rightChild->colour=='B'){
                             siblingNode->leftChild->colour=='B';
                             siblingNode->colour='R';
                             rotateTreeRight(siblingNode);
                             siblingNode=inputNode->parent->rightChild;
                      }
                      siblingNode->colour=inputNode->parent->colour;
                      inputNode->parent->colour='B';
                      siblingNode->rightChild->colour='B';
                      rotateTreeLeft(inputNode->parent);
                      inputNode=root;
                  }
          }else{
                  siblingNode=inputNode->parent->leftChild;
                  if(siblingNode->colour=='R'){
                        siblingNode->colour='B';
                        inputNode->parent->colour='R';
                        rotateTreeRight(inputNode->parent);
                        siblingNode=inputNode->parent->leftChild;
                  }
                  if(siblingNode->leftChild->colour=='B'&&siblingNode->rightChild->colour=='B'){
                        siblingNode->colour='R';
                        inputNode=inputNode->parent;
                  }else{
                        if(siblingNode->leftChild->colour=='B'){
                              siblingNode->rightChild->colour='B';
                              siblingNode->colour='R';
                              rotateTreeLeft(siblingNode);
                              siblingNode=inputNode->parent->leftChild;
                        }
                        siblingNode->colour=inputNode->parent->colour;
                        inputNode->parent->colour='B';
                        siblingNode->leftChild->colour='B';
                        rotateTreeRight(inputNode->parent);
                        inputNode=root;
                  }
          }
       inputNode->colour='B';
       root->colour='B';
    }
}

RbTreeNode* getSuccessorNode(RbTreeNode *inputNode)
{
    RbTreeNode *successorNode=NULL;
    if(inputNode->leftChild!=NULL){
         successorNode=inputNode->leftChild;
         while(successorNode->rightChild!=NULL){
			successorNode=successorNode->rightChild;
		 }  
     }else{
         successorNode=inputNode->rightChild;
         while(successorNode->leftChild!=NULL){
			successorNode=successorNode->leftChild; 
		 }  
     }
     return successorNode;
}

void deleteNode(int deleteElement)
{
     if(root==NULL)
     {
           cout<<"\nEMPTY" ;
           return ;
     }
     RbTreeNode *temp;
     temp=root;
     RbTreeNode *tempRoot=NULL;
     RbTreeNode *tempChild=NULL;
     int flag=0;
     while(temp!=NULL&&flag==0){
           if(temp->value==deleteElement){
			   flag=1;
		   }  
           if(flag==0){
                if(temp->value<deleteElement){
					temp=temp->rightChild; 
				}else{
					temp=temp->leftChild; 
				}
           }
     }
     if(flag==0){
        cout<<"\nABSENT";
        return ;
     }else{
         if(temp->leftChild==NULL||temp->rightChild==NULL){
			tempRoot=temp; 
		 }else{
			tempRoot=getSuccessorNode(temp); 
		 }
         if(tempRoot->leftChild!=NULL){
			tempChild=tempRoot->leftChild; 
		 }else{
              if(tempRoot->rightChild!=NULL){
				tempChild=tempRoot->rightChild;  
			  }else{
				tempChild=NULL;  
			  }
         }
         if(tempChild!=NULL){
			tempChild->parent=tempRoot->parent; 
		 }
         if(tempRoot->parent==NULL){
			root=tempChild; 
		 }else{
             if(tempRoot==tempRoot->parent->leftChild){
				tempRoot->parent->leftChild=tempChild; 
			 }else{
				tempRoot->parent->rightChild=tempChild; 
			 }
		  }
         if(tempRoot!=temp){
             temp->colour=tempRoot->colour;
             temp->value=tempRoot->value;
         }
         if(tempRoot->colour=='B'){
			deleteNodeFix(tempChild); 
		 }   
     }
}

int main()
{
    int ch;
   do{
       //cout<<"Enter choice of element: ";
       cin>>ch;
       switch(ch){
           case 1:{
                int inputElement;
                cin>>inputElement;
                insertNode(inputElement);
            break;   
           }
           case 3:{
                if(root==NULL){
                   cout<<"EMPTY \n"; 
                }else{
                    int inputElement;
                    cin>>inputElement;
                    searchElement(inputElement);
                }
            break;      
           }
           case 2:{
				if(root==NULL){
                   cout<<"EMPTY \n"; 
                }else{
                   int delElement;
				   cin>>delElement;
				   deleteNode(delElement);
                }
            break;
           }
           case 4:{
               displayTreeElements(root);
            break;      
           }
           default:{
            break;      
           }
       }
   }while(ch<=4);
}