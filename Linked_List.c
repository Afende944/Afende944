#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

/*I Alexis Fenderson here certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus
 */

 typedef struct _sampleNode {
    int ID;
    double value;
    struct _sampleNode *next;
 
 } sampleNode;

    typedef struct _dataSet {
        
        sampleNode * samples;
        int nSamples;
        double minSample;
        double maxSample;

        } dataSet;

/* Returns 1 if the data set is empty, or 0 otherwise*/
int isEmpty(dataSet set) {

    int nSamples; 
    int size;

    for(int a = 0; a < nSamples; a++) {
     a = nSamples; // Remember to increment nSamples based on the func

    if (nSamples == 0) {
    return 1;

    } else 
    return 0;

    }

}

  /*
    Searches thru the nodes in the data set and updates the
    maxSample attribute with the largest SampleNode value. The function should be invoked
    for every addition/removal of nodes.
    */

    void updateMax(dataSet * set) { // Same logic as min 

        sampleNode *currentNode = set -> samples;  
        set -> maxSample = currentNode -> value;  
    
        while (currentNode != NULL) {  
            if (currentNode -> value > set -> maxSample) { // compare the currentNode with MaxSample
                set -> maxSample = currentNode -> value; // which points to head first
            }
            currentNode = currentNode -> next; 
        }
    } // again void so no return

   /* Searches thru the nodes in the data set and updates the
      minSample attribute with the smallest SampleNode value. This should be invoked for
       every addition/removal of nodes.*/

    void updateMin(dataSet * set) {
    
    sampleNode *currentNode = set -> samples; 
    set -> minSample = currentNode -> value;   

    while (currentNode != NULL) { // As long as current isnt null
        if (currentNode -> value < set -> minSample) { //Go to value and compare it with current, if its less then it will become the new min
            set -> minSample = currentNode -> value; // if its less then it will become the new min
        }
        currentNode = currentNode -> next; // continue
    } //its void so no return
}


/* Dynamically allocate a new SampleNode to be added to the LinkedList in the DataSet, with an associated value given.
   Add the new node to the head of the list. If the sampleID is present in the list, return-1. 
   Return 0 if the sampleID is successfully added to the list. The updateMax(..) and
   updateMin(..) methods should be used here to update the max/min values in case they
    change from the addition. Remember to update the nSamples parameter as well.
*/

    int addSample(dataSet * set, int SampleID, double value) {

        sampleNode *freshNode = (sampleNode *)malloc(sizeof(sampleNode));
        *freshNode = (sampleNode){SampleID, value, set -> samples}; 
    
        // If there is no head, set head

        if (set -> samples == NULL) {
            set -> samples = freshNode;  

        } else {
            // there is a head so freshNode becomes the new head
            freshNode -> next = set -> samples; //Point freshNode to the current head
            set -> samples = freshNode; //Update the head to the new node
        }

            // Check if the current nodes unique id matches SampleID
            sampleNode *currentNode = set->samples;{
            if (currentNode -> ID == SampleID) {
                free(freshNode);
                return -1; //If so return -1
            } 
            currentNode = currentNode->next;
        }

        updateMax(set);
        updateMin(set);
        set -> nSamples++; //nSamples need to change since we added one
    
        return 0; //Else it should be added as a new node eventually so return 0
    }

    /*
    Searches through the linkedlist in the DataSet, and searches for the SampleNode with the given sampleID.
     The pointer given by location is initially uninitialized. Returns a pointer to the SampleNode if the 
     node with matching sampleID is found. Returns NULL if the sampleID is not found,
     the value pointed to by location being updated to-1. Otherwise, the data associated
     with the location pointer is set to the node’s position on the list (with 0 corresponding to
     the head).
    */
   
    sampleNode* findSample(dataSet set, int SampleID, int * location) {

        int nSamples; // location is updated by whatever node we are at
        sampleNode tempNode = *(set.samples);

        for(int index = 0; index < nSamples; index++) {
    
        if (tempNode.ID == SampleID) {
        *location = index;

        }
         else
        
        if(tempNode.ID != SampleID) { // Return null if sampleID is not found
            *location = -1; //value pointed by location being -1
            return NULL;
    
        }
    }
}

    int size(dataSet set) { // Returns size of the set
        int num = 0;
        sampleNode *currentNode = set.samples; //Non pointer so use .

        while (currentNode != NULL) { // Basic count sequence
        num++;
        currentNode = currentNode -> next; 

        }

        return num;  //i think i could use set.nSamples
    }

    /*
    Removes the head sample from the DataSet, and updates
    the head to the next item in the list. The associated dynamic memory should be freed. The
     updateMax(..) and updateMin(..) methods should be used here to update the max/min
     values in case they change from the removal. Remember to update the nSamples parameter
    as well.
    */

    int removeSample(dataSet * set) {

        sampleNode *removableNode = set->samples; //Make a removed node set to head
        set -> samples = removableNode -> next;  //the new node is whatever is after the removed head
        free(removableNode); // free the memory
    
        updateMin(set);  //update both these guys
        updateMax(set); 
 
        set -> nSamples--; //nSamples decreases

        return 0; 
    }

    /*
    Dynamically frees the entire set of nodes in the LinkedList,
    along with the data associated with the DataSet struct
    */

    void deleteSet(dataSet * set) {

        for (sampleNode *current = set -> samples; current != NULL; ) { //Current is set to the head, as long as it is not null
            sampleNode *nextNode = current -> next; // go to the next node
            free(current); // free said node
            current = nextNode; //head to next node
        }
    }

    /*
    This method prints the address of each SampleNode,
    along with the ID and value of the sample to the console.
    */
    void printSamples(dataSet * set) {

        sampleNode *freshnode = set -> samples;

        while (freshnode != NULL) {
            printf("Node address is: %p\n", freshnode); // Print adress, ID and value of node
            printf("Node ID is: %i\n",  freshnode -> ID);
            printf("Node value is: %.2f\n", freshnode -> value); // Just to make the formatting look nicer

            freshnode = freshnode -> next;
        }

    }

    /*
    Takes a file name file, and populates the DataSet linked list with SampleNodes data (double) values separated by
     space given in the file. 
 
    *PARAM*
    You may assume that an empty Dataset Struct has been initialized
    outside the function. 
    
    There must be no assumption about the number of data values in
    the file. The filename is taken as an optional command line argument.
    */

    void initalizeFromFile(const char * file, dataSet * set) {

        FILE *readFile = fopen(file, "r"); //open and read file
        double value;
        set -> samples = NULL;            
    
        while (fscanf(readFile, "%lf", &value) == 1) {  
            sampleNode *freshNode = (sampleNode *)malloc(sizeof(sampleNode));  
            freshNode ->value = value;   
            freshNode -> next = NULL;     
    
            if (set -> samples == NULL) {  // If the list is empty
                set -> samples = freshNode;  // The new node becomes the head
            } else {
                sampleNode *holdTemp = set -> samples; // Make the temp node head

                while (holdTemp -> next ) { // Whiles theres a next
                    holdTemp = holdTemp -> next; //temp.ext 

                }
                holdTemp -> next = freshNode; //temp.next = New node
        }

    }
    
        fclose(readFile); 
        

    }

// Include your data structures and function definitions here
// For simplicity, the code includes the structs, but it assumes you've already defined them in your code above

int main(int argc, char *argv[]) {

}

    /* Resources: 
       Understanding and Using C Pointers,
       GeeksforGeeks, 
       C programming for dummies, 
       Intermediate C Programming,
       stackoverflow 
    */




