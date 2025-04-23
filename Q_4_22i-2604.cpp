// Counts discrepancies in gadget quality scores
#include <iostream>
#include <vector>

using namespace std;

// Merges subarrays and counts inversions
long long merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;      // Left subarray index 
    int j = mid + 1;   // Right subarray index
    int k = left;      // Temp array index
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1); // Count inversions
        }
    }

    // Copy remaining elements
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // Copy back to original array
    for (i = left; i <= right; i++) arr[i] = temp[i];

    return invCount;
}

// Divides array and counts inversions
long long mergeSort(vector<int>& arr, vector<int>& temp, int left, int right) {
    long long invCount = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSort(arr, temp, left, mid);        // Process left half
        invCount += mergeSort(arr, temp, mid + 1, right);   // Process right half
        invCount += merge(arr, temp, left, mid, right);     // Merge halves
    }

    return invCount;
}

// Wrapper function to count inversions
long long countInversions(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);
    return mergeSort(arr, temp, 0, n - 1);
}

int main() {
    int t;
    cin >> t;  // Test cases

    while (t--) {
        int n;
        cin >> n;  // Number of gadgets

        vector<int> scores(n);

        // Read scores
        for (int i = 0; i < n; i++) cin >> scores[i];

        // Output disorder count
        cout << countInversions(scores) << endl;
    }

    return 0;
}