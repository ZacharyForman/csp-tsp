#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define D(i,j) (d[(j) * (n) + (i)])

int branch_and_bound(int *d, int n, int *p, int l,
                     int c, int b, int *bp, char *s)
{
  if (c >= b) return b;

  if (l == n) {
    memcpy(bp, p, n * sizeof(int));
    return c;
  }

  int i;
  for (i = 0; i < n; i++) {
    if (s[i]) continue;
    s[i] = 1;
    p[l] = i;
    c += D(p[l-1], i);
    int t = branch_and_bound(d, n, p, l+1, c, b, bp, s);
    if (t < b) {
      b = t;
    }
    c -= D(p[l-1], i);
    s[i] = 0;
  }
  return b;
}

int main(int argc, char **argv)
{
  int n;
  int *d;

  FILE *f = fopen(argv[1], "r");
  if (!f) {
    fprintf(stderr, "bad file %s\n", argv[1]);
    return -1;
  }
  fscanf(f, "%d", &n);
  d = malloc(sizeof(int) * n * n);
  int i,j;

  for (i = 0; i < n; i++) {
    D(i,i) = 0;
    for (j = 0; j < i; j++) {
      fscanf(f, "%d", &D(i,j));
      D(j,i) = D(i,j);
    }
  }

  int *p = calloc(n, sizeof(int));
  int *bp = calloc(n, sizeof(int));
  char *s = calloc(n, sizeof(int));
  s[0] = 1;
  p[0] = 0;
  int b = branch_and_bound(d, n, p, 1, 0, INT_MAX, bp, s);

  printf("Path:");
  for (i = 0; i < n; i++) {
    printf(" %d", bp[i]+1);
  }
  printf(": %d\n", b);

  return 0;
}
