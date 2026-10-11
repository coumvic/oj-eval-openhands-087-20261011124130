#include <iostream>
#include <vector>

int main() {
    int D;
    long long n;
    std::cin >> D >> n;
    
    // Calculate the final position of the last ball
    // The path of the k-th ball corresponds to the binary representation of k-1
    // Read from LSB to MSB, where 0=left, 1=right
    // The position is 1 followed by the reversed bits of (k-1)
    
    // For the last ball (k = n), we use k-1 = n-1
    long long path_bits = n - 1;
    int position = 1;  // Start with the root
    
    // Add D-1 bits to the position, from LSB to MSB of path_bits
    for (int i = 0; i < D - 1; i++) {
        // Check the i-th bit of path_bits (starting from 0)
        if (path_bits & (1LL << i)) {
            // Bit is set, go right
            position = position * 2 + 1;
        } else {
            // Bit is not set, go left
            position = position * 2;
        }
    }
    
    // Output the final position
    std::cout << position << std::endl;
    
    // Now calculate the final states of leaf nodes
    // Leaf nodes are at positions 2^(D-1) to 2^D - 1
    int leaf_start = 1 << (D - 1);
    int leaf_count = 1 << (D - 1);
    
    std::vector<int> leaf_states(leaf_count, 0);
    
    // For each leaf node, determine if an odd number of balls passed through it
    for (int i = 0; i < leaf_count; i++) {
        int leaf_pos = leaf_start + i;
        
        // Extract the path bits for this leaf
        // The path is encoded in the last D-1 bits of the position
        // We need to reverse these bits to get the target for ball path
        int temp = leaf_pos;
        long long target = 0;
        // Remove the leading 1
        temp >>= (D - 1);
        // Now extract the D-1 bits and reverse them
        for (int j = 0; j < D - 1; j++) {
            if (leaf_pos & (1 << j)) {
                target |= (1LL << (D - 2 - j));
            }
        }
        
        // Count how many balls have path matching this leaf
        // Balls k where k-1 has the target bits in the first D-1 bits
        // i.e., (k-1) mod 2^(D-1) == target
        long long modulus = 1LL << (D - 1);
        long long count = 0;
        
        if (target < n) {
            // Number of integers in [0, n-1] congruent to target mod modulus
            count = ((n - 1 - target) / modulus) + 1;
        }
        
        // Leaf state is 1 if odd number of balls passed through it
        leaf_states[i] = (count % 2 == 1) ? 1 : 0;
    }
    
    // Output leaf states
    for (int i = 0; i < leaf_count; i++) {
        if (i > 0) std::cout << " ";
        std::cout << leaf_states[i];
    }
    std::cout << std::endl;
    
    return 0;
}