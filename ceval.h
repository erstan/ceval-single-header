#ifndef CEVAL
#define CEVAL
//functions accessible from main() 
// - double ceval_result(char * inp) returns the result of valid math expression stored as a char array `inp`
// - void ceval_tree(char * inp) prints the parse tree for the input expression `inp`

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
/*****************************************************************************************/
typedef enum ceval_node_id {
  CEVAL_WHITESPACE,
  CEVAL_OPENPAR, CEVAL_CLOSEPAR,
  CEVAL_COMMA,
  CEVAL_POSSIGN, CEVAL_NEGSIGN,
  CEVAL_PLUS, CEVAL_MINUS, 
  CEVAL_TIMES, CEVAL_DIVIDE, CEVAL_MODULO, CEVAL_QUOTIENT,
  CEVAL_ABS, CEVAL_POW, CEVAL_EXP, CEVAL_SQRT, CEVAL_CBRT, CEVAL_LN, CEVAL_LOG10, CEVAL_CEIL, CEVAL_FLOOR, CEVAL_POWFUN, CEVAL_ATAN2, CEVAL_GCD, CEVAL_HCF, CEVAL_LCM, CEVAL_LOG, CEVAL_INT, CEVAL_FRAC,
  CEVAL_FACTORIAL,
  CEVAL_SIN, CEVAL_COS, CEVAL_TAN, CEVAL_ASIN, CEVAL_ACOS, CEVAL_ATAN, CEVAL_SINH, CEVAL_COSH, CEVAL_TANH,
  CEVAL_DEG2RAD, CEVAL_RAD2DEG,
  CEVAL_SIGNUM,
  CEVAL_LESSER, CEVAL_GREATER, CEVAL_LESSER_S, CEVAL_GREATER_S,
  CEVAL_EQUAL, CEVAL_NOTEQUAL,
  CEVAL_NUMBER
}ceval_node_id;
const char * ceval_token_symbol[] = {
  " ",
  "(", ")",
  ",",
  "+", "-",
  "+", "-",
  "*", "/", "%", "\\",
  "abs", "^", "exp", "sqrt", "cbrt", "ln", "log10", "ceil", "floor", "pow", "atan2", "gcd", "hcf", "lcm", "log", "int", "frac",
  "!",
  "sin", "cos", "tan", "asin", "acos", "atan", "sinh", "cosh", "tanh",
  "deg2rad", "rad2deg", 
  "signum",
  "<=", ">=", "<", ">", 
  "==", "!=",
  " "
};
const double ceval_precedence[] = {
  0,
  1, 1,
  1.5,
  3, 3, 
  2, 2, 
  4, 4, 4, 4, 
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6,
  7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7,
  7,
  1.2, 1.2, 1.2, 1.2,
  1.1, 1.1,
  10
};
ceval_node_id ceval_singlechar_token_id(char token) {
  switch (token) {
  case '(':
    return CEVAL_OPENPAR;
  case ')':
    return CEVAL_CLOSEPAR;
  case '+':
    return CEVAL_PLUS;
  case '-':
    return CEVAL_MINUS;
  case '*':
    return CEVAL_TIMES;
  case '/':
    return CEVAL_DIVIDE;
  case '%':
    return CEVAL_MODULO;
  case '\\':
    return CEVAL_QUOTIENT;
  case '^':
    return CEVAL_POW;
  case '!':
    return CEVAL_FACTORIAL;
  case ',':
    return CEVAL_COMMA;
  case '<':
    return CEVAL_LESSER_S;
  case '>':
    return CEVAL_GREATER_S;
  default:
    if ('0' <= token && token <= '9') return CEVAL_NUMBER;
    else if (token == ' ' || token == '\t' || token == '\r' || token == '\n') return CEVAL_WHITESPACE;
  }
  return CEVAL_OPENPAR;
}
typedef struct ceval_node {
  enum ceval_node_id id;
  double pre;
  double number;
  struct ceval_node * left, * right, * parent;
} ceval_node;

#ifdef __cplusplus
  #define CEVAL_CXX
  #include<iostream>
  #include<string>
#endif
/************************************************************************************/

//constant definitions
const float CEVAL_CONST_PI = M_PI;
const float CEVAL_CONST_E = M_E;
#ifndef EPSILON
  #define EPSILON 1e-2
#endif
#ifndef DELTA
  #define DELTA 1e-6
#endif
//these can be defined by the user before the include directive depending the desired level of precision

//helper function prototypes
void ceval_error(const char *);
double ceval_gcd_binary(int, int);
char * ceval_shrink(char *);

//single argument funtion prototypes
double ceval_signum(double);
double ceval_asin(double);
double ceval_acos(double);
double ceval_atan(double);
double ceval_sin(double);
double ceval_cos(double);
double ceval_tan(double);
double ceval_sinh(double);
double ceval_cosh(double);
double ceval_tanh(double);
double ceval_rad2deg(double);
double ceval_deg2rad(double);
double ceval_int_part(double);
double ceval_frac_part(double);
double ceval_log10(double);
double ceval_ln(double);
double ceval_exp(double);
double ceval_factorial(double);
double ceval_positive_sign(double);
double ceval_negative_sign(double);
double ceval_abs(double);
double ceval_sqrt(double);
double ceval_sqrt(double);
double ceval_cbrt(double);
double ceval_ceil(double);
double ceval_floor(double);

//double argument function prototypes
double ceval_sum(double, double, int);
double ceval_diff(double, double, int);
double ceval_prod(double, double, int);
double ceval_div(double, double, int);
double ceval_quotient(double, double, int);
double ceval_modulus(double, double, int);
double ceval_gcd(double, double, int);
double ceval_hcf(double, double, int);
double ceval_lcm(double, double, int);
double ceval_log(double, double, int);
double ceval_are_equal(double, double, int);
double ceval_not_equal(double, double, int);
double ceval_lesser(double, double, int);
double ceval_greater(double, double, int);
double ceval_lesser_s(double, double, int);
double ceval_greater_s(double, double, int);
double ceval_comma(double, double, int);
double ceval_power(double, double, int);
double ceval_atan2(double, double, int);

//helper function definitions
void ceval_error(const char * error) {
  if (strcmp(error, "")) printf("\n[ceval]: %s\n", error);
}
double ceval_gcd_binary (int a, int b) {
  if(a == 0 && b == 0) 
    return 0;
  while(b) 
    b ^= a ^= b ^= a %= b;
return a;
}
char * ceval_shrink(char * x) {
  char * y = x;
  int len = 0;
  for (int i = 0; i < strlen(x); i++) {
    if (x[i] != ' ' || x[i] != '\t') {
      *(y + len) = tolower(x[i]);
      len++;
    } else {
      continue;
    }
  }
  y[len] = '\0';
  return y;
}

//single argument function definitions
double (*single_arg_fun[]) (double) = {
  NULL,
  NULL, NULL,
  NULL,
  ceval_positive_sign, ceval_negative_sign, 
  NULL, NULL,
  NULL, NULL, NULL, NULL,
  ceval_abs, NULL, ceval_exp, ceval_sqrt, ceval_cbrt, ceval_ln, ceval_log10, ceval_ceil, ceval_floor, NULL, NULL, NULL, NULL, NULL, NULL, ceval_int_part, ceval_frac_part,
  ceval_factorial,
  ceval_sin, ceval_cos, ceval_tan, ceval_asin, ceval_acos, ceval_atan, ceval_sinh, ceval_cosh, ceval_tanh,
  ceval_deg2rad, ceval_rad2deg, 
  ceval_signum,
  NULL, NULL, NULL, NULL,
  NULL, NULL,
  NULL
};
double ceval_signum(double x) {
  return (x==0)?0:
          (x>0)?1:
          -1;
}
double ceval_asin(double x) {
  if (x > 1 || x < -1) {
    ceval_error("Numerical argument out of domain");
    return NAN;
  }
  return asin(x);
}
double ceval_acos(double x) {
  if (x > 1 || x < -1) {
    ceval_error("Numerical argument out of domain");
    return NAN;
  }
  return acos(x);
}
double ceval_atan(double x) {
  return atan(x);
}
double ceval_sin(double x) {
  double sin_val = sin(x);
  //sin(pi) == 0.000000, but sin(pi-EPSILON) == -0.00000* and sin(pi+EPSILON) == +0.00000*
  //since the precision of pi (approx) is limited, it often leads to -0.0000 printed out as a result
  //thus, we assumse 0.0000 value for all |sin(x)|<=EPSILON
  return (fabs(sin_val) <= EPSILON) ? 0 : sin_val;
}
double ceval_cos(double x) {
  double cos_val = cos(x);
  return (fabs(cos_val) <= EPSILON) ? 0 : cos_val;
}
double ceval_tan(double x) {
  double tan_val = tan(x);
  if(abs(ceval_modulus(x - CEVAL_CONST_PI/2, CEVAL_CONST_PI, 0)) <= DELTA) {
    ceval_error("tan() is not defined for odd-integral multiples of pi/2");
    return NAN;
  }
  return (fabs(tan_val) <= EPSILON) ? 0 : tan_val;
}
double ceval_rad2deg(double x) {
  return x / CEVAL_CONST_PI * 180;
}
double ceval_deg2rad(double x) {
  return x / 180 * CEVAL_CONST_PI;
}
double ceval_int_part(double x) {
  double x_i, x_f;
  x_f = modf(x, &x_i);
  return x_i;
}
double ceval_frac_part(double x) {
  double x_i, x_f;
  x_f = modf(x, &x_i);
  return x_f;
}
double ceval_log10(double x) {
  return ceval_log(10, x, 0);
}
double ceval_ln(double x) {
  return ceval_log(CEVAL_CONST_E, x, 0);
}
double ceval_exp(double x) {
  return ceval_power(CEVAL_CONST_E, x, 0);
}
double ceval_factorial(double x) {
  return tgamma(x + 1);
}
double ceval_positive_sign(double x) {
  return x;
}
double ceval_negative_sign(double x) {
  return -x;
}
double ceval_abs(double x) {
  return fabs(x);
}
double ceval_sqrt(double x) {
  if(x>=0) return sqrt(x);
  ceval_error("sqrt(): can't operate on negative numbers");
  return NAN;
}
double ceval_cbrt(double x) {
  return cbrt(x);
}
double ceval_ceil(double x) {
  return ceil(x);
}
double ceval_floor(double x) {
  return floor(x);
}
double ceval_sinh(double x) {
  return sinh(x);
}
double ceval_cosh(double x) {
  return cosh(x);
}
double ceval_tanh(double x) {
  return tanh(x);
}

//double argument function definitions
//double argument function definitions
double (*double_arg_fun[]) (double, double, int) = {
  NULL,
  NULL, NULL,
  ceval_comma,
  NULL, NULL,
  ceval_sum, ceval_diff,
  ceval_prod, ceval_div, ceval_modulus, ceval_quotient,
  NULL, ceval_power, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ceval_power, ceval_atan2, ceval_gcd, ceval_hcf, ceval_lcm, ceval_log, NULL, NULL, 
  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
  NULL, NULL, 
  NULL, 
  ceval_lesser, ceval_greater, ceval_lesser_s, ceval_greater_s,
  ceval_are_equal, ceval_not_equal,
  NULL
};
double ceval_sum(double a, double b, int arg_check) {
  return a + b;
}
double ceval_diff(double a, double b, int arg_check) {
  return a - b;
}
double ceval_prod(double a, double b, int arg_check) {
  return a * b;
}
double ceval_div(double a, double b, int arg_check) {
  if (b == 0 && a == 0) {
    ceval_error("0/0 is indeterminate...");
    ceval_error("Continuing evaluation with the assumption 0/0 = 1");
    return 1;
  } else if (b == 0) {
    ceval_error("Division by 0 is not defined...");
    ceval_error("Continuing evaluation with the assumption 1/0 = inf");
    return a * INFINITY;
  }
  return a / b;
}
double ceval_modulus(double a, double b, int arg_check) {
  if (b == 0) {
    ceval_error("Division by 0 is not defined...");
    ceval_error("Continuing evaluation with the assumption 1%0 = 0");
    return 0;
  }
  return fmod(a, b);
}
double ceval_quotient(double a, double b, int arg_check) {
  //a = b*q + r
  //q = (a - r)/b
  if (b == 0 && a == 0) {
    ceval_error("0/0 is indeterminate...");
    ceval_error("Continuing evaluation with the assumption 0/0 = 1");
    return 1;

  } else if (b == 0) {
    ceval_error("Division by 0 is not defined...");
    ceval_error("Continuing evaluation with the assumption 1/0 = inf");
    return a * INFINITY;
  }
  return (a - ceval_modulus(a, b, 0)) / b;
}
double ceval_gcd(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("gcd(): too few arguments provided");
    return NAN;
  }
  double a_f = ceval_frac_part(a),
         b_f = ceval_frac_part(b);
  int a_i = ceval_int_part(a), 
      b_i = ceval_int_part(b);
  if(a_f == 0 && b_f == 0) {
    return (double) ceval_gcd_binary(a_i, b_i);
  } else {
    ceval_error("gcd() takes only integral parameters");
    return NAN;
  }
}
double ceval_hcf(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("hcf(): too few arguments provided");
    return NAN;
  }
  return ceval_gcd(a, b, 0);
}
double ceval_lcm(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("lcm(): too few arguments provided");
    return NAN;
  }
  return a * b / ceval_gcd(a, b, 0);
}
double ceval_log(double b, double x, int arg_check) {
  if (arg_check) {
    ceval_error("log(): too few arguments provided");
    return NAN;
  }
  if(b == 0) {
    if(x == 0) {
      ceval_error("log(0,0) is indeterminate");
      return NAN;
    } else {
      return 0;
    }
  }
  return log(x) / log(b);
}
double ceval_are_equal(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("==: too few arguments provided");
    return NAN;
  }
  if (fabs(a - b) <= EPSILON) {
    return 1;
  } else {
    return 0;
  }
}
double ceval_not_equal(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("!=: too few arguments provided");
    return NAN;
  }
  return !ceval_are_equal(a, b, 0);
}
double ceval_lesser(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("<=: too few arguments provided");
    return NAN;
  }
  return (b - a) >= EPSILON;
}
double ceval_greater(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error(">=: too few arguments provided");
    return NAN;
  }
  return (a - b) >= EPSILON;
}
double ceval_lesser_s(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error("<: too few arguments provided");
    return NAN;
  }
  return !ceval_greater(a, b, 0);
}
double ceval_greater_s(double a, double b, int arg_check) {
  if (arg_check) {
    ceval_error(">: too few arguments provided");
    return NAN;
  }
  return !ceval_lesser(a, b, 0);
}
double ceval_comma(double x, double y, int arg_check) {
  if (arg_check) {
    ceval_error(",: too few arguments provided");
    return NAN;
  }
  return y;
}
double ceval_power(double x, double y, int arg_check) {
  if (arg_check) {
    ceval_error("pow(): too few arguments provided");
    return NAN;
  }
  return pow(x, y);
}
double ceval_atan2(double x, double y, int arg_check) {
  if (arg_check) {
    ceval_error("atan2(): too few arguments provided");
    return NAN;
  }
  return atan2(x, y);
}

/************************************************************************************/
void * ceval_make_tree(char *);
ceval_node * ceval_insert_node(ceval_node *, ceval_node, int);
void ceval_print_tree(const void *);
void ceval_print_node(const ceval_node *, int);
void ceval_delete_node(ceval_node *);
void ceval_delete_tree(void *);

void ceval_delete_node(ceval_node * node) {
  if (!node) return;
  ceval_delete_node(node -> left);
  ceval_delete_node(node -> right);
  free(node);
}
void ceval_delete_tree(void * tree) {
  ceval_delete_node((ceval_node * ) tree);
}
ceval_node * ceval_insert_node(ceval_node * current, ceval_node item, int isRightAssoc) {
  if (item.id != CEVAL_OPENPAR &&
    item.id != CEVAL_NEGSIGN &&
    item.id != CEVAL_POSSIGN) {
    if (isRightAssoc) {
      while (current -> pre > item.pre) {
        current = current -> parent;
      }
    } else {
      while (current -> pre >= item.pre) {
        current = current -> parent;
      }
    }
  }
  if (item.id == CEVAL_CLOSEPAR) { 
    ceval_node * parent_of_openpar = current -> parent;
    parent_of_openpar -> right = current -> right;
    if (current -> right) current -> right -> parent = parent_of_openpar;
    free(current);
    current = parent_of_openpar;

    if (current -> right -> id == CEVAL_COMMA && 
       (current -> id == CEVAL_POWFUN || current -> id == CEVAL_ATAN2 || 
        current -> id == CEVAL_GCD || current -> id == CEVAL_HCF || current -> id == CEVAL_LCM ||
        current -> id == CEVAL_LOG)) {
      ceval_node * address_of_comma = current -> right;
      parent_of_openpar -> left = address_of_comma -> left;
      address_of_comma -> left -> parent = parent_of_openpar;
      parent_of_openpar -> right = address_of_comma -> right;
      address_of_comma -> right -> parent = parent_of_openpar;
      free(address_of_comma);
    }
    return current;
  }
  ceval_node * newnode = (ceval_node * ) malloc(sizeof(ceval_node));
  * newnode = item;
  newnode -> right = NULL;

  newnode -> left = current -> right;
  if (current -> right) current -> right -> parent = newnode;
  current -> right = newnode;
  newnode -> parent = current;
  current = newnode;
  return current;
}

void * ceval_make_tree(char * expression) {
  if (expression == NULL) return NULL;
  strcpy(expression, ceval_shrink(expression));
  ceval_node root = {
    CEVAL_OPENPAR,
    ceval_precedence[CEVAL_OPENPAR],
    0,
    NULL,
    NULL,
    NULL
  };
  ceval_node_id previous_id = CEVAL_OPENPAR;
  ceval_node * current = & root;
  int isRightAssoc = 0;
  while (1) {
    ceval_node node;
    char c = * expression++; 
    isRightAssoc = (c == '^' || c == ')') ? 1 : 0; 
    if (c == '\0') break;
    else if (ceval_singlechar_token_id(c) == CEVAL_WHITESPACE) continue;
    else if (c == '(' || c == ')') {
      node.id = ceval_singlechar_token_id(c);
      node.pre = ceval_precedence[node.id];
    } else if (ceval_singlechar_token_id(c) == CEVAL_NUMBER) {
      node.pre = ceval_precedence[CEVAL_NUMBER];
      int i;
      char number[15];
      for (i = 0; i + 1 < sizeof(number);) {
        number[i++] = c;
        c = * expression;
        if (ceval_singlechar_token_id(c) == CEVAL_NUMBER || c == '.')
          expression++;
        else break;
      }
      number[i] = '\0';
      sscanf(number, "%lf", & node.number);
      node.id = CEVAL_NUMBER;
    } else if (c == '+' || c == '-' || 
      c == '*' || c == '/' || c == '%' || c == '\\' ||
      c == '^' ||
      (c == '!' && * (expression) != '=') || 
      (c == '!' && * (expression) == '=' && * (expression + 1) == '=') ||
      (c == '<' && * (expression) != '=') ||
      (c == '>' && * (expression) != '=') ||
      c == ',') {
      if (previous_id == CEVAL_NUMBER || previous_id == CEVAL_CLOSEPAR || previous_id == CEVAL_FACTORIAL) {
        node.id = ceval_singlechar_token_id(c);
        node.pre = ceval_precedence[node.id];
      } else {
        if (c == '-') {
          node.id = CEVAL_NEGSIGN;
          node.pre = ceval_precedence[node.id];
        } else if (c == '+') {
          node.id = CEVAL_POSSIGN;
          node.pre = ceval_precedence[node.id];
        } else {
          printf("[ceval]: Misplaced '%c' sign\n", c);
          return NULL;
        }
      }
    } else if (!memcmp(expression - 1, "pi", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CEVAL_CONST_PI;
    } else if (!memcmp(expression - 1, "exp", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_EXP;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "e", 1)) {
      expression = expression + (1 - 1);
      node.id = CEVAL_NUMBER;
      node.pre = ceval_precedence[node.id];
      node.number = CEVAL_CONST_E;
    } else if (!memcmp(expression - 1, "abs", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_ABS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sqrt", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_SQRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cbrt", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_CBRT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ceil", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_CEIL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "floor", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_FLOOR;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "pow", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_POWFUN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan2", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_ATAN2;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "ln", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_LN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log10", 5)) {
      expression = expression + (5 - 1);
      node.id = CEVAL_LOG10;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "log", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_LOG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sinh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_SINH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cosh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_COSH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tanh", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_TANH;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "sin", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_SIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "cos", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_COS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "tan", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_TAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "asin", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ASIN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "acos", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ACOS;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "atan", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_ATAN;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "deg2rad", 7)) {
      expression = expression + (7 - 1);
      node.id = CEVAL_DEG2RAD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "rad2deg", 7)) {
      expression = expression + (7 - 1);
      node.id = CEVAL_RAD2DEG;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "signum", 6)) {
      expression = expression + (6 - 1);
      node.id = CEVAL_SIGNUM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "gcd", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_GCD;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "hcf", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_HCF;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "lcm", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_LCM;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "int", 3)) {
      expression = expression + (3 - 1);
      node.id = CEVAL_INT;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "frac", 4)) {
      expression = expression + (4 - 1);
      node.id = CEVAL_FRAC;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "<=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_LESSER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, ">=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_GREATER;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "==", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_EQUAL;
      node.pre = ceval_precedence[node.id];
    } else if (!memcmp(expression - 1, "!=", 2)) {
      expression = expression + (2 - 1);
      node.id = CEVAL_NOTEQUAL;
      node.pre = ceval_precedence[node.id];
    } else {
      printf("[ceval]: Unknown token '%c'.\n", c);
      ceval_delete_tree(root.right);
      root.right = NULL;
      break;
    }
    previous_id = node.id;
    current = ceval_insert_node(current, node, isRightAssoc);
  }
  if (root.right) root.right -> parent = NULL;
  return root.right;
}
void ceval_print_node(const ceval_node * node, int indent) {
  int i;
  char number[20];
  const char * str;
  if (!node) return;
  ceval_print_node(node -> right, indent + 4);
  if(node->id == CEVAL_NUMBER) {
    if ((long) node -> number == node -> number) //for integers, skip the trailing zeroes
      sprintf(number, "%.0f", node -> number);
    else sprintf(number, "%.2f", node -> number);
    str = number;
  }else{
    str = ceval_token_symbol[node->id];
  }
  for (i = 0; i < indent; i++) {
    putchar(' ');
    putchar(' ');
  }
  puts(str);
  ceval_print_node(node -> left, indent + 4);
}

void ceval_print_tree(const void * tree) {
  ceval_print_node((const ceval_node * ) tree, 0);
}

/***************************************************************************************/
double ceval_evaluate_tree_(const ceval_node *);
double ceval_evaluate_tree(const void *);

double ceval_evaluate_tree_(const ceval_node * node) {
  if (!node) return 0;
  double left, right;
  left = ceval_evaluate_tree_(node -> left);
  right = ceval_evaluate_tree_(node -> right);
  switch (node -> id) {
  
  //unary operators/functions
  case CEVAL_NEGSIGN: case CEVAL_POSSIGN:
  case CEVAL_EXP: case CEVAL_LN: case CEVAL_LOG10:
  case CEVAL_ABS: case CEVAL_CEIL: case CEVAL_FLOOR:
  case CEVAL_SQRT: case CEVAL_CBRT:
  case CEVAL_SIN: case CEVAL_COS: case CEVAL_TAN: 
  case CEVAL_ASIN: case CEVAL_ACOS: case CEVAL_ATAN:
  case CEVAL_SINH: case CEVAL_COSH: case CEVAL_TANH:
  case CEVAL_DEG2RAD: case CEVAL_RAD2DEG:
  case CEVAL_SIGNUM: case CEVAL_INT: case CEVAL_FRAC: case CEVAL_FACTORIAL:
    if(node->left == NULL) {
      //operate on right operand
      return (*single_arg_fun[node->id])(right);
    } else if(node->right == NULL) { 
      //operate on left operand(e.g; factorial())
      return (*single_arg_fun[node->id])(left);
    }
  
  //binary operators/functions
  case CEVAL_PLUS: case CEVAL_MINUS:
  case CEVAL_TIMES: case CEVAL_DIVIDE: case CEVAL_MODULO: case CEVAL_QUOTIENT:
  case CEVAL_POW: case CEVAL_POWFUN:
  case CEVAL_ATAN2: case CEVAL_GCD: case CEVAL_HCF: case CEVAL_LCM: case CEVAL_LOG:
  case CEVAL_LESSER: case CEVAL_LESSER_S: case CEVAL_GREATER: case CEVAL_GREATER_S:
  case CEVAL_EQUAL: case CEVAL_NOTEQUAL:
  case CEVAL_COMMA:
    if(node->left == NULL) {
      return (*double_arg_fun[node->id])(left, right, -1);
    } else if (node->right == NULL) {
      return (*double_arg_fun[node->id])(left, right, 1);
    } else {
      return (*double_arg_fun[node->id])(left, right, 0);
    }
  default:
    return node -> number;
  }
}
double ceval_evaluate_tree(const void * node) {
  return ceval_evaluate_tree_((ceval_node * ) node);
}


double ceval_result(char * expr) {
  void * tree = ceval_make_tree(expr);
  double result = ceval_evaluate_tree(tree);
  ceval_delete_tree(tree);
  #ifdef CEVAL_ERROR
      printf("Error encountered\n");
      #undef CEVAL_ERROR
      return 0;
  #endif
  return result;
}
void ceval_tree(char * expr) {
  void * tree = ceval_make_tree(expr);
  #ifdef CEVAL_ERROR
      printf("Error encountered\n");
      #undef CEVAL_ERROR
      return;
  #endif
  ceval_print_tree(tree);
  ceval_delete_tree(tree);
}
#ifdef CXX
  #include<iostream>
  #include<cstring>
  double ceval_result(std::string expr){
    return ceval_result((char *)expr.c_str());
  }
  void ceval_tree(std::string expr) {
    ceval_tree((char *)expr.c_str());
  }
#endif
#endif
