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
"       li		$4, 0x800			\n" // Numero total de elementos en bytes (2048 = 256*8*64)
"		li		$5, 0x10 			\n" // Moverse de a 2 elementos porque es lo que entra en los registros vectoriales de MSA de 128 bits
"		move	$6, %[Ra]			\n" // Mover el puntero al array a
"		move	$7, %[Rb]			\n" // Mover el puntero al array b
"		move	$8, %[Rc]			\n" // Mover el puntero al array c
"		move	$9, %[Rd]			\n" // Mover el puntero al array d

"loop:	LD.D	$w0, 0($7)			\n" // Cargar 2 elementos de b
"       LD.D    $w1, 0($8)           \n" // Cargar 2 elementos de c
"       FADD.D  $w3, $w0, $w1       \n" // w3 <- b[i] + c[i] 
"       st.D    $w3, 0($6)          \n" // a[i] <- b[i] + c[i]

"       LD.D    $w2, 0($9)          \n" // Cargar 2 elementos de d
"       FMUL.D  $w4, $w3, $w7       \n" //  w4 <- A*3 (A is w3)
"       CEQ.D   $w6, $w0, $w1       \n" // A = B?
"       BSEL.V  $w6, $w4, $w2       \n" // Si a[i] = b[i] copio desde w4, si no desde el d[i] original
"       st.D    $w6, 0($9)          \n" // Store updated d[i]


"       SUB     $4, $4, $5          \n" // Decrementar con los restantes usados
"       DADD    $6, $6, $5          \n" // Mover las direcciones base
"       DADD    $7, $7, $5          \n"
"       DADD    $8, $8, $5          \n"
"       DADD    $9, $9, $5          \n"
"       bnez    $4, loop            \n"
"       nop                         \n"





:
: [Ra] "r" (a),
  [Rb] "r" (b),
  [Rc] "r" (c),
  [Rd] "r" (d),
  [Rthree] "r" (three),
  [Rfive] "r" (five)
: "memory", "$4", "$5", "$6", "$7", "$8", "$9"
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
