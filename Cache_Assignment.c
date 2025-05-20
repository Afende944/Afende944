#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

/*I Alexis Fenderson here certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus
 */

 /*
 Cache: Using typedef and struct create a compound data type Cache, with struct name
 _cache. Cache have the following attributes:

 int size: The total size in Bytes. Obtained from the console. This value is equal to
 the number of blocks times 16

 int blockSize: The size of a block, which is 16 Bytes
 
 int hits: Represents the number of hits from cache requests (initially 0)

 int misses: Represents the number of misses from cache requests (initially 0)

 int sets: Represents the number of sets in the cache (obtained from console in main)

 int blocks: Represents the number of blocks in the cache (Computed based upon total
 size and the number of sets)

  int * cacheInfo: A pointer to an array of cache lines. Each element of the array
 represents a 32 bit Hexadecimal address. The array is dynamically allocated. The
 first element (cache block) will correspond to set 0. Depending on the number of lines
 in a set, the second element may or may not be in set 0. You may assume sets are
 ordered numerically in order in the array
 
 */

 typedef struct _cache {
    int size;
    int blocksize;
    int hits;
    int misses;
    int sets;
    int blocks;    
    int Time;
    int * cacheInfo;
    int * aTime;

 } Cache; 

 /*
 int computeTag(int address, Cache* cache): Computes the tag of an address, given the
 parameters of the cache.
 */

 int computeTag(int address, Cache * cache) {

    // The tag is whats left from the offset and the set, so we just remove those first 

    int Blocks = address / cache -> blocksize; // Removing the offset
    int Tagcalculated = Blocks / cache -> sets;  // Then we remove the sets
          
    return Tagcalculated; // Whats left is the tag

 }

 /*
 int computeSet(int address, Cache* cache): Computes the associated set of an address,
 given the parameters of the cache.
 */

 int computeSet(int address, Cache * cache) {

    int Setcalculation = (address / cache -> blocksize ) % cache -> sets;  // Similar to tag, we want sets instead of tag so %

    return Setcalculation; // This could also be one statement but its easier to understand this way
 }


 /*
 int addItem(int address, Cache* cache): 
 
 Adds an entire cache block to cache with the starting address as given.
 PARAM Assume all requests are 16 Bytes. 
 
 If all of the associated blocks associated with a set are full, you may replace a block at random (but it must go in the
 appropriate set). 
 
 The replacement must be random. You may use the random(..) function,
 which is part of the stdlib. Note that the old block should no longer be in cache.
 
 */

 int addItem(int address, Cache * cache) {

    int Set = computeSet(address, cache); // We already made the logic for Set, set lines and tag
    int Tag = computeTag(address, cache); // So we can just reuse the same logic
    int lines = cache -> blocks / cache -> sets;

    // Try to find an empty slot
    for (int x = 0; x < lines; x++) { // Increment through loop to find empty
        int Cacheindex = (Set * lines) + x;

        if (cache -> cacheInfo[Cacheindex] == -1) { //If we find an empty spot
           cache -> cacheInfo[Cacheindex] = Tag; // We set that index as the tag
           cache -> aTime[Cacheindex] = cache -> Time++; //Time counter for the LRU function

            return 0;
        }
    }

    int Randomreplc = (Set * lines) + (rand() % lines); // If its full, randomly pick a line to replace
    Tag = cache -> cacheInfo[Randomreplc]; // Then set the tag equal to that new Randomplace

    return 0;
}
 

 /*
 int inCache(int address, Cache * cache): Calls the associated computeTag and computeSet
 functions in order to determine whether an item is in cache.
 
 If an address has a matching tag for a block in the appropriate set, it is in cache.
 
 The function should return 1 if the block if present in cache.
 This function should update the hits and misses of cache as well.

 The function should call the addItem() function when an item is not in cache and return
 0
 */

 int inCache(int address, Cache * cache) {

      int Set = computeSet(address, cache); //Basically the same logic as addItem but if it exist in cache
      int Tag = computeTag(address, cache); // Then we identify a hit (and if not a miss)
      int lines = cache -> blocks / cache -> sets;
  
   
      for (int x = 0; x < lines; x++) { // Loop through cache lines
        int Cacheindex = (Set * lines) + x; // Set index (Not literally)

        
          if (cache -> cacheInfo[Cacheindex] == Tag) { //If the cache index is the matching tag
              cache -> hits++;  // We found a hit and thus it increments 
              cache -> aTime[Cacheindex] = cache -> Time++;
              return 1; //First Param: Returns 1 if present in cache
          }
    
      } 

        cache -> misses++;  // If not then its a miss and miss increments instead
        addItem(address, cache); //Second Param: The function should call the addItem() function when an item is not in cache 
        
        return 0; // And return 0
    
      }

 /*
 double hitRatio(Cache * cache): Computes and returns the current hit ratio of cache.
 */

 double hitRatio(Cache * cache) {
    int accessAm = cache -> misses + cache -> hits; // Amount of hits and misses

    if (accessAm == 0) { // It shouldnt be zero but just encase to catch anything
        return 0.00;   // Returning a double

    } else {
        return (double) cache -> hits / accessAm; // We just wants hits so divide it out
    } // (Note) make sure return is a double by casting
} // Test weren't working properly without

 /*
 double missRatio(Cache * cache): Computes and returns the current miss ratio of cache.
 */

 double missRatio(Cache * cache) {

    int accessAm = cache -> misses + cache -> hits; // Amount of hits and misses

    if (accessAm == 0) { // It shouldnt be zero but just encase to catch anything
        return 0.00;   // Returning a double

    } else {
        return (double) cache -> misses / accessAm; // Same thing as before
    } // Cast aswell
}

 /*
 Extra Credit: int * computeLRU(int address, Cache * cache). 
 
 Computes and returns the a pointer to the least recently used cache line associated with a given set.
  Note that if you choose to implement this function, you will need to add additional metadata to support
 this feature.
 
 */

 int * computeLRU(int address, Cache * cache) {

    int Set = computeSet(address, cache); // Same as the others
    int Tag = computeTag(address, cache); // Though I dont think we need tag
    int lines = cache -> blocks / cache -> sets;
    int LRUIndex = Set * lines; // Least recently used index


    for (int y = 1; y < lines; y++) { // Loop through starting a 1 since we created a basepoint
        int SEIndex = LRUIndex + y; // Create a base index based on LRUindex and its incrementation

        if (cache -> aTime[LRUIndex] > cache -> aTime[SEIndex]) { // If the LRU access time is greater than the base index access time (IE Older)
            LRUIndex = SEIndex; // Set the LRU index to the base
        }
    }

       int *LRU = &cache -> cacheInfo[LRUIndex]; // The point to the memory address of the Index in cache

       return LRU; // And return that value
}

void freeMem(Cache * cache) { // Free all dynamically allocated memory once it is no longer needed.
    free(cache -> cacheInfo); 
    free(cache -> aTime);    
    free(cache);           
}

 /*
 int main(int argv, char *argv[]) : From the console, the cache size parameters are obtained.
 These include the total size and the number of sets. The number of sets is at least 1 (fully
 associated), and must divide evenly with the number of blocks. For example if the total
 size is 256 Bytes, and each block is 16 bytes, then there are 16 blocks, and hence there
 can be 1, 2, 4, 8, or 16 sets. Once the parameters are obtained, a cache struct should be
 initialized with appropriate values and dynamically allocated memory.
 */

 int main(int argc, char * argv[]) { 

}

  /* Resources: 
       Understanding and Using C Pointers,
       GeeksforGeeks, 
       stackoverflow 
       Computer Architecture: A Quantitative Approach
    */