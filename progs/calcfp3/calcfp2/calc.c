#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>


float add(float a, float b){
	return a + b;
}

float sub(float a, float b){
	return a - b;
}
float divi(float a, float b){
	return a / b;
}

float mul(float a, float b){
	return a * b;
}

typedef struct calc{
	/*float (*addition)(float, float);
	float (*subtraction)(float, float);
	float (*division)(float, float);
	float (*multiplication)(float, float);
	float (*sine)(float);
	float (*cosine)(float);
	float (*tangent)(float);*/
	float (*unary_op)(float);
	float (*binary_op)(float, float);

} calc;

int main(int argc, char **argv){	
	calc c;
	/*c.addition = add;
	c.division = divi;
	c.subtraction = sub;
	c.multiplication = mul;
	c.sine = sinf;
	c.cosine = cosf;
	c.tangent = tanf;*/
	char buf[20];
	int pc;
	
	if (argc != 3 && argc != 4){
		printf("Format either oprnd operator oprnd OR sin/cos/tan rad\n");
		exit(EXIT_SUCCESS);
	}

	if (strcmp(argv[1],"sin") == 0){
		c.unary_op = sinf;
		printf("Sin(%f) = %f",atof(argv[2]),c.unary_op(atof(argv[2])));
	}
	else if (strcmp(argv[1],"cos") == 0 ){
		c.unary_op = cosf;
		printf("Cos(%f) = %f",atof(argv[2]),c.unary_op(atof(argv[2])));
	}
	else if (strcmp(argv[1],"tan") == 0){
		c.unary_op = tanf;
		printf("Tan(%f) = %f",atof(argv[2]),c.unary_op(atof(argv[2])));
	}

	else{
		switch(*argv[2]){
			case '+':
			c.binary_op = add;
			break;
			case '-':
			c.binary_op = sub;
			break;
			case 'x':
			c.binary_op = mul;
			break;
			case '/':
			c.binary_op = divi;
			break;
			default:
			perror("?");
			break;
		}
		pc = sprintf(buf, "%f", c.binary_op(atof(argv[1]), atof(argv[3])));
		write(1, buf, pc);
		
	}
	return 0;


}	
