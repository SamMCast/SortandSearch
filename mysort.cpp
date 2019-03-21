#include <cstdlib>      // std::rand, std::srand
#include <stdio.h>
#include <getopt.h>
#include <algorithm> 
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <ctime>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <string>
#include <random>
#include <sstream>      // std::stringstream


using namespace std;

void print_usage(){
  printf("Usage: sort -r <max and min range> -s <selection sort> -u <uniform> -m <merge sort> -q <quicksort>\n");
  exit(2);
}

int findSmallest(const vector<int> & nums, int start){
  int size = (int)nums.size();
  int minIdx = start;

  for(;start < size; ++start){
    if(nums[minIdx] > nums[start]){
      minIdx = start;
    }
  }

  return minIdx;
}

bool linearSearch(const vector<int> & nums, int item){
  for (int i = 0; i < nums.size(); ++i){
    if(item == nums[i]){
      return true;
    }
  }

  return false;
}

bool interpolationSearch(const vector<int> & nums, int item){
  int low = 0;
  int pos;
  int high = nums.size()-1;

  while (low <= high && item >= nums[low] && item <= nums[high]) 
    { 
       // Probing the position with keeping 
        // uniform distribution in mind. 
        int pos = low + (((double)(high - low) / (nums[high] - nums[low])) * (item - nums[low])); 
  
        // Condition of target found 
        if (nums[pos] == item) 
            return true; 
  
        // If item is larger, item is in upper part 
        if (nums[pos] < item) 
            low = pos + 1; 
  
        // If item is smaller, item is in the lower part 
        else
            high = pos - 1; 
    } 

  return false;
}

bool binarySearch(const vector<int> & nums, int item){

  int low = 0;
  int high = nums.size()-1;
  int mid;

  while(low <= high){
     mid = low + (high - low)/2;
    if(nums[mid] < item){
      low = mid +1;
    }
    else if (nums[mid] > item){
      high = mid -1;
    }
    else {
      return true;
    }
  }

  return false;
}

vector<int> selectionSort(const vector<int> & nums){
  vector<int> sortArry(nums.size());
  copy(nums.begin(), nums.end(), sortArry.begin());

  printf("\n--------------------Selection Sort----------------------------\n");

  int bestIdx;

  for (size_t i = 0; i < sortArry.size(); ++i){
    bestIdx = findSmallest(sortArry, i);
    swap(sortArry[bestIdx], sortArry[i]);
  }

  return sortArry;

}

vector <int> quickSort(const vector<int> & nums){
  vector<int> Arry(nums.size());
  copy(nums.begin(), nums.end(), Arry.begin());

  printf("\n---------------------Quick Sort--------------------------------\n");

  return Arry;
}

void merge(vector<int> & nums, int low, int mid, int high){

  int leftstart = low;
  int rightstart = mid+1;

  int size = high - low + 1;
  int index = -1;
  vector<int> temp (size);

  while(leftstart <= mid && rightstart <= high){
    if(nums[leftstart] <= nums[rightstart]){
        temp[++index] = nums[leftstart];
        ++leftstart;
    }
    else {
      temp[++index] = nums[rightstart];
      ++rightstart;
    }
  }
  ++index;
  copy(nums.begin() + leftstart, nums.begin() + mid+1, temp.begin() + index);
  copy(nums.begin() + rightstart, nums.begin() + high+1, temp.begin() + index);
  copy(temp.begin(), temp.end(), nums.begin() + low);

}

void mergesort(vector<int> & nums, int low, int high){
  if(low == high){
    return;
  }

  int mid = low + (high - low)/2;
  mergesort(nums, low, mid);
  mergesort(nums, mid + 1, high);
  merge(nums, low, mid, high);
}

vector<int> mergeSort(const vector<int> & nums){
  vector<int> Arry(nums.size());
  copy(nums.begin(), nums.end(), Arry.begin());

  printf("\n---------------------Merge Sort--------------------------------\n");
  mergesort(Arry, 0, nums.size()-1);

  return Arry;
}

/**
 * @param string, min value and max value seperated by a comma
 * uses the min and max value to determine the size and the range of values in the list
 * @return vector<int>, a vector of integers with the min and max value specified by the string
 */
vector <int> randomize_vector(string range, bool UFlag){
  char delimiter = ',';
  size_t pos = range.find(delimiter);

  int range1 = stoi(range.substr(0, pos));
  int end = range.size();

  // Check if the end user entered second delimeter
  size_t pos2 = range.find(delimiter, pos + 1);

  //The item wasn't found
  if(pos2 == string::npos){
    pos2 = range.size(); 
  }
  
  int range2 = stoi(range.substr(pos + 1, pos2));

  int minrange = (range1 <= range2) ? range1: range2;
  int maxrange = (range1 <= range2) ? range2: range1;

  int capacity = maxrange - minrange+1;

  vector<int> nums(capacity);
  int size = -1;

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> dis(minrange, maxrange);

  vector<bool> Bitset(capacity);

  for (int i = 0; i < capacity; ++i){
    int number = dis(gen);
    if(!UFlag || (UFlag && !Bitset[number - minrange]))
      nums[++size] = number;
  
    Bitset[number-minrange] = true;
  }
  
  nums.resize(++size);
  
  return nums;

}

int grabIn(const int maxattempts, int ifFail, string message){
  int option;
  int attempts = 0;

  cin >> option;
  bool cinFail = cin.fail();


  while(cinFail){
    ++attempts;
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printf("Invalid input. Try again. You have %d attempts remaining.\n", maxattempts - attempts);
    if(attempts == maxattempts){
      return ifFail;
    }
    printf("%s ", message.c_str());
    cin >> option;
    cinFail = cin.fail();
  }

  return option;

}

void searchMethods(const vector<int> & nums, string message ){
  
  bool isValid = false;
  bool found;

  int option, searchItem, userChoice;
  int attempts = 0;
  isValid = false;
  clock_t start, end;
  double elasped;

  do {
    printf("Enter 0 to perform a linear search\n");
    printf("Enter 1 to perform a binary seach\n");
    printf("Enter 2 to perform an interpolation search\n");
    printf("Enter 3 to exit\n");

    stringstream ss("Enter option: ");

    printf("Enter option: ");
    userChoice = grabIn(5, -1, ss.str());
    int ifFail = nums[0]-1;
    if(userChoice != -1 && userChoice != 3){
      printf("Enter number to be searched: ");
      ss.str("Enter number to be searched: ");
      searchItem = grabIn(3, ifFail, ss.str());
    }

    option = (ifFail == searchItem || userChoice == -1) ? -1 : userChoice;


    printf("-----------------------------------------------------------------------------------\n");
    printf("%s ", message.c_str());

    switch(option){
      case 0:
        start = clock();
        found = linearSearch(nums, searchItem );
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC * 1000;
        if(found)
          printf("Linear search was able to");
        else
          printf("Linear search wasn't able to");

        printf(" locate the item in %.6f milliseconds\n", elasped);
      break;
      case 1:
        start = clock();
        found = binarySearch(nums, searchItem );
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC * 1000;
        if(found)
          printf("Binary search was able to");
        else
          printf("Binary search wasn't able to");

        printf(" locate the item in %.6f milliseconds\n", elasped);
      break;
      case 2:
        start = clock();
        found = interpolationSearch(nums, searchItem );
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC * 1000;
        if(found)
          printf("Interpolation search was able to");
        else
          printf("Interpolation search wasn't able to");

        printf(" locate the item in %.6f milliseconds\n", elasped);
      break;

      case -1:
        printf("Error too failed attempts. Exiting.\n");
      case 3:
        isValid = true;
      break;
    }

  
  }while(!isValid);
  
}

void parseArguments(const vector<char> & commands, vector<int> & nums){
 
  const int viewSize = 50;
  vector<int> arry;
  std::stringstream ss;
  clock_t start, end;
  double elasped;
  if(nums.size() <= viewSize){
    printf("Do you wish view if the contents of the vector. Enter 1 for yes: ");
    ss.str("Do you wish view if the contents of the vector. Enter 1 for yes: ");
    int usrRep = grabIn(1, 0, ss.str());
    if(usrRep)
      copy(nums.begin(), nums.end(), ostream_iterator<int>(cout, ", "));
      printf("\n");
  }

  for(int i = 0; i < commands.size(); ++i){
    switch(commands[i]){
      case 's':
        start = clock();
        arry = selectionSort(nums);
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC;
        ss << "Selection Sort took "<< elasped << " seconds to complete. ";
        searchMethods(arry, ss.str());
        ss.str(std::string());

        //copy(arry.begin(), arry.end(), ostream_iterator<int>(cout, ", "));
        break;
      case 'q':
        printf("Quick Sort hasn't been implemented yet.\n");
        /*
        start = clock();
        arry = quickSort(nums);
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC;
        ss << "Quick Sort took "<< elasped << " seconds to complete. ";
        searchMethods(arry, ss.str());
        */
        break;
      case 'm':
        start = clock();
        arry = mergeSort(nums);
        end = clock();
        elasped = (double) (end-start) / CLOCKS_PER_SEC;
        ss << "Merge Sort took "<< elasped << " seconds to complete. ";
        searchMethods(arry, ss.str());
        ss.str(std::string());
      break;        
    }
  }
}




int main(int argc, char * argv []){
  const int maxargcs = 2;

  if(argc <  maxargcs){
    print_usage();
   }

  int opt;
  vector<char> commands;
  vector<int> nums;
  string size;
  bool UFlag = false;

// Parse command line arguments 
  while((opt = getopt(argc, argv, ":r:msqu")) != -1){
    switch(opt){
      case 'r':     // initialize a vector of size optarg
        size = optarg;
        if(!isdigit(size[0])){
          print_usage();
        }
        break;

      case 'u':
        UFlag = true;
        break;

      case 's':
      case 'q':
      case 'm':
        commands.push_back(opt);
        break;

      case ':':  // The user entered a flag but not an associated value
        printf(" Error. Option needs a value\n");
        print_usage();
        break;

      case '?':  // The user entered an unknown flag
        printf("Unknown option: %c\n", optopt);
        print_usage();
        break;
    }
   }

  nums = randomize_vector(size, UFlag);
  parseArguments(commands, nums); 

}

