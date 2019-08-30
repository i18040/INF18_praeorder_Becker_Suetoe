#include <stdio.h>
#include <stdlib.h>

struct tnode {
	int content; /* Knoteninhalt */
	struct tnode *left; /* linker Teilbaum */
	struct tnode *right; /* rechter Teilbaum */
	struct tnode *parent;
};

void * malloc(size_t size);

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* addelement: neuen Knoten einfuegen */
struct tnode *addelement(struct tnode *p, int i) {
	int cond;
	if (p == NULL) {
		p = talloc(); /* make a new node */
		p->content = i;
		p->left =p->right =p->parent =NULL;
	} else if (p->content == i) {
		return p;
	} else if (i < p->content){ /* nach links gehen */
		p->left =addelement(p->left, i);
		p->left->parent = p;
	}
	else{ /* nach rechts gehen */
		p->right = addelement(p->right, i);
		p->right->parent = p;
	}
	return p;
}

void free(void *ptr);

/* loescht Knoten mit allen Soehnen */
int deletenode(struct tnode *p) {
	if (p == NULL) return 0;
	else {
		deletenode(p->left);
		deletenode(p->right);
		p->left = NULL;
		p->right = NULL;
		free(p);
		return 0;
	}
}

struct tnode *addtree(struct tnode *top, struct tnode *p) {
	if (p == NULL)
		return top;
	else
		return addtree(addtree(addelement(top, p->content),p->
			right), p->left);
}

//zeigt baum in der praeorderreihenfolge
int showpraeorder(struct tnode *p){
	printf("%d\n", p->content);
	if(p == NULL) return 0;
	if(p->left != NULL){
	showpraeorder(p->left);
	}
	if(p->right != NULL){
	showpraeorder(p->right);
	}
	
}

//findet Element mit content i im Baum
struct tnode *findelement(struct tnode *node, int i){
	if (node->content > i){
		return(findelement(node->left, i));
	}
	else if(node->content < i){
		
		return(findelement(node->right, i));
	}
	else if(node->content == i){
		return(node);
	}
	else{
		return NULL;
	}
}

//findet das nächste zum tauschen im echten teilbaum
struct tnode *findclosestright(struct tnode *node){
	if(node->left != NULL){
		return(findclosestright(node->left));
	}
	else{
		return (node);
	}
}

//entfernt ein element und behält die unterbäume (falls existent)
struct tnode *deleteelement(struct tnode *node, int i){
	struct tnode *p = findelement(node, i);
	struct tnode *childtree;
	struct tnode *child;
	if (p == NULL){
		return(node);
	}
	else{
		//falls Blatt
		if(p->left == NULL && p->right == NULL){
			struct tnode *parent = p->parent;
			struct tnode *child = p;
			deletenode(p);
			if(parent->left == child){
				parent->left=NULL;
			}
			else{
				parent->right=NULL;
			}
			return(node);
		}
		//falls eine Seite leer
		else if((p->left == NULL) || (p->right == NULL)){
			struct tnode *parent = p->parent;
			struct tnode *child = p;
			struct tnode *childtree = NULL;
			if(child->left != NULL){
				childtree = child->left;
			}
			else{
				childtree = child->right;
			}			
			if(parent->left == child){
				parent->left=NULL;
			}
			else{
				parent->right=NULL;
			}
			addtree(node, childtree);
			deletenode(child);
			return(node);
		}
		//falls beide seiten mindestens ein blatt
		else{
			struct tnode *closest = findclosestright(p->right);
			int k = closest->content;
			deleteelement(node,k);
			p->content = k;
			return(node);
		}
	}	
}


void main(){

	//baue Beispielbaum, hier können Sie Ihre einträge machen
	struct tnode *baum = addelement(NULL, 5);
	addelement(baum,6);
	addelement(baum,3);
	addelement(baum,9);
	addelement(baum,1);
	addelement(baum,4);
	addelement(baum,12);
	addelement(baum,7);
	addelement(baum,8);
	addelement(baum,10);
	addelement(baum,11);
	addelement(baum,13);
	addelement(baum,14);
	// zeige den baum praeorder an
	printf("Baum in Praeorder Reihenfolge:\n\n");
	showpraeorder(baum);
	printf("\n");
	//entferne element aus baum mit content i
	printf("Element wird nun aus Baum entfernt...\n");
  //Beispiel delete, einfach den Baum und den Wert, den man entfernt haben will eintragen als Parameter
	deleteelement(baum, 12);
	//zeige neuen baum
	printf("Element erfolgreich entfernt, aktualisierter Baum wird angezeigt:\n\n");
	showpraeorder(baum);
	
}
