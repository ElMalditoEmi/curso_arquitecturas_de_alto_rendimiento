# int8_t a[]; int32_t b[], c[];
# for (i=0; i<n; i++) { b[i] = (a[i] < 5) ? c[i] : 1; }
#
# Register arguments:
# a0 n
# a1 a
# a2 b
# a3 c

loop:
    vsetvli t0, a0, e8, m1, ta, ma
    vle8.v v0, (a1)
        add a1, a1, t0
    vmslt.vi v0, v0, 5 # Mask, (if < 5)
    
    vsetvli t0, a0, e32, m4, ta, ma
        slli t0, t0, 2

    vmv.v.i v4, 1 # Splat 1 on result
    vle32.v v4, (a3), v0.t # Cargar c[] donde la mascara permita

    vse32.v v4, (a2) # Store v4 on b[]
    add a2, a2, t0 # Mover a la proxima direccion base de b[]


        sub a0, a0, t0 # n - k
    bnez a0, loop # If n > 0, loop

