#include <stdio.h>

// Safe starting position
int safeStart(int n, int k) {
  int safe_pos = 0;  // Safe position for 1 person (0-based)
  for (int i = 2; i <= n; i++) {
    safe_pos = (safe_pos + k) % i;
  }
  return safe_pos + 1;  // Convert to 1-based index
}

int main() {
  int n, k;

  while (1) {
    // Read input values for n and k
    // n is num of ppl
    // k is step size
    scanf("%d %d", &n, &k);

    if (n == 0 && k == 0) {
      break;
    }

    // Calculate the safe starting position
    int safe_start = safeStart(n, k);

    // safe starting position
    printf("%d\n", safe_start);
  }

  return 0;
}