#include "cub3d.h"

int	anglizer(float vx1, float vy1, float vx2, float vy2)
{
	float determinant;

	determinant = vx1 * vy2 - vx2 * vy1;
	if (determinant >= 0)
		return (1);
	else
		return (-1);
}