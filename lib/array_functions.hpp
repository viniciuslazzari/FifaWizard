#ifndef array_functions_h
#define array_functions_h

#include <iostream>
#include <vector>

int getMax(std::vector<int> array){
    int max = array[0];

    for (int number : array)
        if (number > max) max = number;  

    return max; 
}
  
std::vector<int> countingSort(std::vector<int> array, int size, int div){ 
    int aux[size];
    int digit_position;
    int count[10] = { 0 }; 
  
    for (int i = 0; i < size; i++) 
        count[(array[i] / div) % 10]++; 
  
    for (int i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    for (int i = size - 1; i >= 0; i--){ 
        digit_position = (array[i] / div) % 10;

        aux[count[digit_position] - 1] = array[i]; 
        count[digit_position]--; 
    } 
  
    for (int i = 0; i < size; i++) 
        array[i] = aux[i];

    return array;
}
 
std::vector<int> radixSort(std::vector<int> array){
    int m = getMax(array);

    for (int div = 1; m / div > 0; div *= 10) 
        array = countingSort(array, array.size(), div); 

    return array;
}

std::vector<int> intersection(std::vector<int> arr1, std::vector<int> arr2){
    std::vector<int> aux;

    arr1 = radixSort(arr1);
    arr2 = radixSort(arr2);

    for (int number1 : arr1){
        for (int number2 : arr2){
            if (number1 == number2){
                aux.push_back(number1);
                break;
            }
        }        
    }

    return aux;
}

std::vector<int> removeDups(std::vector<int> arr){
    std::vector<int> aux;
    bool found;

    for (int number1 : arr){
        found = false;

        for (int number2 : aux){
            if (number1 == number2){
                found = true;
            }
        }    

        if (!found) aux.push_back(number1);
    }

    return aux;
}

template <class type>
void swap(type* a, type* b){
    type t = *a;
    *a = *b;
    *b = t;
}

double getObjSortingAttribute(Rating obj){
    return (double)obj.score;
}

double getObjSortingAttribute(Player obj){
    return (double)obj.score_total / obj.score_count;
}

double getObjSortingAttribute(PlayersModel obj){
    return obj.median;
}

template <class type>
float partition(std::vector<type>* array, int low, int high){
    double pivot = getObjSortingAttribute((*array)[high]);
    int i = low - 1;

    for (int j = low; j < high; j++){
        if (getObjSortingAttribute((*array)[j]) <= pivot){
            i++;
            swap(&((*array)[i]), &((*array)[j]));
        }
    }

    swap(&((*array)[i + 1]), &((*array)[high]));

    return i + 1;
}

template <class type>
std::vector<type> quicksortObj(std::vector<type> array, int low, int high){
    if (low < high){
        int pi = partition(&array, low, high);
        array = quicksortObj(array, low, pi - 1);
        array = quicksortObj(array, pi + 1, high);
    }

    return array;
}

#endif