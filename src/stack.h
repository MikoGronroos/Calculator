#define input_length 32

typedef enum type{
   Number,
   Substraction,
   Addition,
   Multiplication,
   Division,
   Sqrt,
   Sin,
   Cos,
   Tan,
   Power,
   LBracket,
   RBracket
} type;

typedef struct content{
   type type;
   char input[input_length];
} content;

typedef struct stack{
   content** stack;
   int count;
} stack;

int add(stack* stack, char* input, type type);
content* pop(stack* stack);
stack* allocateNewStack();
int freeStack(stack* target);
