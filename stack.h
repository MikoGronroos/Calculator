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
   Power
} type;

typedef struct content{
   type type;
   char* input;
} content;

typedef struct stack{
   content** stack;
   int count;
} stack;

int add(stack* stack, content* item);
content* pop(stack* stack);
stack* allocateNewStack();
int freeStack(stack* target);
