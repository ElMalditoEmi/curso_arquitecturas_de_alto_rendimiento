# void add_cond (size_t n, float a, float* X, float* Y){
# size_t i;
# for (i=0; i<n; i++)
# if (X[i] !== 0) Y[i] = X[i] + Y[i];
# }
# Register arguments:
# a0 n -- no usado en esta version
# a1 X
# a2 Y
# a3 Z -- no usado en esta version


loop:
    vsetvli t0, a0, e32, m1,ta, ma
    

    vle32.v v0, (a1) # v0 <- X[]
    vfeq32.vi v1, v0, 0 # Setear en v1 la mascara para X = 0
    vmnot.m v1, v1    # Negar la mascara (X!=0)

    vle32.v v3, (a2) # v3 <- Y[]
    vfadd.vv v3, v3, v1, v0.t # Y = X + Y, if X != 0

    vse32.v v3, (a2) # Store modified Y

        sub a0, a0, t0 # n - k

        slli t0, t0, 2 # Offset para las nuevas direcciones base 
        add a1, a1, t0 # Mover las
        add a2, a2, t0 # direcciones base

    bnez a0, loop




    
