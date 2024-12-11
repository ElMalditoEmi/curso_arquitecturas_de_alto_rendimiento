#include <stdio.h>
#include <msa.h>

__attribute__((aligned(16))) double a[256], b[256], c[256], d[256];
__attribute__((aligned(16))) double three[] = {3.0,3.0};
__attribute__((aligned(16))) double five[] = {5.0,5.0};

int main()
{

int i,j;

// fake test image (red channel)
for (i=0; i<256; i++) {
    b[i] = c[i]= (double)(i)/10;
    d[i] = 0.0;
}

c[5] = 0.0;

//#define SIMD_VERSION

#ifdef MSA_VERSION
__asm volatile(
"		LD.D	$w7,0(%[Rthree])	\n"
"		LD.D	$w8,0(%[Rfive])		\n"
// YOUR CODE
:
: [Ra] "r" (a),
  [Rb] "r" (b),
  [Rc] "r" (c),
  [Rd] "r" (d),
  [Rthree] "r" (three),
  [Rfive] "r" (five)
: "memory", "$4", "$5", "$6"
);
#else
for (i=0; i<256; i++) {
    a[i]=b[i]+c[i];
    if (a[i]==b[i])
       d[i]=a[i]*3;
    b[i]=a[i]-5;
}
#endif


// check output
for (i=0; i<256;i++) {
    printf(" a:%lf b:%lf c:%lf d:%lf\n",a[i],b[i],c[i],d[i]);
}

return 0;
}
