#include <stdio.h>
#include "includes/libmat.h"

void printfmat(t_mat4 mat)
{
  for(int i = 0; i < 16;i++)
  {
    printf("%0.2f ", mat.m[i]);
    if (i % 4 == 3)
      printf("\n");
  }
}

int main(void)
{
  t_mat4 mat;
  t_mat4 mat2;
  t_mat4 mat3;
  t_mat4 mat1;

  mat1.m[0] = 3;
  mat1.m[1] = 5;
  mat1.m[2] = 7;
  mat1.m[3] = 8;
  mat1.m[4] = 1;
  mat1.m[5] = 2;
  mat1.m[6] = 8;
  mat1.m[7] = 7;
  mat1.m[8] = 4;
  mat1.m[9] = 5;
  mat1.m[10] = 3;
  mat1.m[11] = -2;
  mat1.m[12] = 1;
  mat1.m[13] = 6;
  mat1.m[14] = 7;
  mat1.m[15] = 9;

  mat2.m[0] = 2;
  mat2.m[1] = 8;
  mat2.m[2] = 6;
  mat2.m[3] = 9;
  mat2.m[4] = 3;
  mat2.m[5] = -5;
  mat2.m[6] = 6;
  mat2.m[7] = 7;
  mat2.m[8] = 1;
  mat2.m[9] = 4;
  mat2.m[10] = 9;
  mat2.m[11] = -3;
  mat2.m[12] = 10;
  mat2.m[13] = -2;
  mat2.m[14] = 5;
  mat2.m[15] = 2;

/*         SET            */
  set_mat4(&mat, 2);
  printf("set\n");
  printfmat(mat);
/*         Identité       */
  mat4_id(&mat);
  printf("id\n");
  printfmat(mat);
/*          ADD           */
  mat3 = mat4_add(mat1, mat2);
  printf("add\n");
  printfmat(mat3);
/*          SUB           */
  mat3 = mat4_sub(mat1, mat2);
  printf("sub\n");
  printfmat(mat3);
/*         MULT           */
  mat3 = mat4_mult(mat1, mat2);
  printf("mult\n");
  printfmat(mat3);
/*        ROTATION        */
mat3 = mat4_rot_axis(mat1, AXIS_X, 60);
printf("rot x\n");
printfmat(mat3);

mat3 = mat4_rot_axis(mat1, AXIS_Y, 60);
printf("rot y\n");
printfmat(mat3);

mat3 = mat4_rot_axis(mat1, AXIS_Z, 60);
printf("rot z\n");
printfmat(mat3);
/*  SCALING               */
mat3 = mat4_scale(mat1, 5);
printf("scale\n");
printfmat(mat3);

  return (0);
}
