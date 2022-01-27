// off-no-diagnostics
// RUN: %clang_cc1 -triple powerpc64-ibm-aix-xcoff -verify -fsyntax-only %s
// RUN: %clang_cc1 -triple powerpc-ibm-aix-xcoff -verify -fsyntax-only %s
// RUN: %clang_cc1 -triple powerpc64-ibm-aix-xcoff -verify=off -Wno-aix-compat -fsyntax-only %s
// RUN: %clang_cc1 -triple powerpc-ibm-aix-xcoff -verify=off -Wno-aix-compat -fsyntax-only %s
// RUN: %clang_cc1 -triple powerpc64le-unknown-linux -verify=off -fsyntax-only %s

struct S {
  int a[8] __attribute__((aligned(8)));  // no-warning
  int b[8] __attribute__((aligned(16))); // no-warning
  int c[2] __attribute__((aligned(32))); // no-warning
};

struct T {
  int a[4] __attribute__((aligned(16))); // no-warning
};

struct U {
  int a[2] __attribute__((aligned(32))); // no-warning
};

int a[8] __attribute__((aligned(8)));  // no-warning
int b[4] __attribute__((aligned(16))); // no-warning
int c[2] __attribute__((aligned(32))); // no-warning

void baz(int *);
void foo(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8,
         struct S s) {
  baz(s.a); // no-warning
  baz(s.b); // expected-warning {{requesting an alignment of 16 bytes or greater for struct members is not binary compatible with IBM XL C/C++ for AIX 16.1.0 and older}}
  baz(s.c); // expected-warning {{requesting an alignment of 16 bytes or greater for struct members is not binary compatible with IBM XL C/C++ for AIX 16.1.0 and older}}

  baz(a); // no-warning
  baz(b); // no-warning
  baz(c); // no-warning
}
