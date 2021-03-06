/* TinyTest: A really really really tiny and simple no-hassle C unit-testing framework.
 *
 * Features:
 *   - No library dependencies. Not even itself. Just a header file.
 *   - Simple ANSI C. Should work with virtually ever C or C++ compiler on
 *     virtually any platform.
 *   - Reports assertion failures, including expressions and line numbers.
 *   - Stops test on first failed assertion.
 *   - ANSI color output for maximum visibility.
 *   - Easy to embed in apps for runtime tests (e.g. environment tests).
 *
 * Example Usage:
 *
 *    #include "tinytest.h"
 *    #include "mylib.h"
 *
 *    void test_sheep()
 *    {
 *      ASSERT("Sheep are cool", are_sheep_cool());
 *      ASSERT_EQUALS(4, sheep.legs);
 *    }
 *
 *    void test_cheese()
 *    {
 *      ASSERT("Cheese is tangy", cheese.tanginess > 0);
 *      ASSERT_STRING_EQUALS("Wensleydale", cheese.name);
 *    }
 *
 *    int main()
 *    {
 *      RUN(test_sheep);
 *      RUN(test_cheese);
 *      return TEST_REPORT();
 *    }
 *
 * To run the tests, compile the tests as a binary and run it.
 *
 * Project home page: http://github.com/joewalnes/tinytest
 *
 * 2010, -Joe Walnes <joe@walnes.com> http://joewalnes.com
 */

#ifndef _TINYTEST_INCLUDED
#define _TINYTEST_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>

/* Main assertion method */
#define ASSERT(msg, expression) if (!tt_assert(__FILE__, __LINE__, (msg), (#expression), (expression) ? true : false)) //return

/* Convenient assertion methods */
/* TODO: Generate readable error messages for assert_equals or assert_str_equals */
#define ASSERT_EQUALS(expected, actual) ASSERT((#actual), (expected) == (actual))
#define ASSERT_STRING_EQUALS(expected, actual) ASSERT((#actual), strcmp((expected),(actual)) == 0)

/* Run a test() function */
#define RUN(test_function) tt_execute((#test_function), (test_function))
#define TEST_REPORT() tt_report()

#define TT_COLOR_CODE 0x1B
#define TT_COLOR_RED "[1;31m"
#define TT_COLOR_GREEN "[1;32m"
#define TT_COLOR_RESET "[0m"

int tt_passes = 0;
int tt_fails = 0;
bool tt_current_test_failed = false;
const char* tt_current_msg = NULL;
const char* tt_current_expression = NULL;
const char* tt_current_file = NULL;
int tt_current_line = 0;
char* tt_current_name = NULL;

typedef struct testinfo{
    const char* file;
    int line;
    const char* msg;
    const char* expression;
    bool pass;
    testinfo* next;
} testinfo;

typedef struct failureInfo{
    const char* current_file;
    int current_line;
    const char* name;
    const char* current_msg;
    const char* current_expression;
    failureInfo* next;

};

testinfo* testH;
failureInfo* failureInfoH;


void tt_execute(const char* name, void (*test_function)())
{
  tt_current_test_failed = false;
    tt_current_name = (char*) malloc(sizeof(name));
    strncpy(tt_current_name,name,sizeof(name));
    //printf("%s",tt_current_name);
  test_function();
  if (tt_current_test_failed) {
      /* replaced below
    printf("failure: %s:%d: In test %s():\n    %s (%s)\n",
      tt_current_file, tt_current_line, name, tt_current_msg, tt_current_expression);
*/

    tt_fails++;
  } else {
    tt_passes++;
  }
}

bool tt_assert(const char* file, int line, const char* msg, const char* expression, bool pass)
{
  tt_current_msg = msg;
  tt_current_expression = expression;
  tt_current_file = file;
  tt_current_line = line;
  tt_current_test_failed = !pass;


    //strncpy(n->file,file,300);
  if(!pass){
    testinfo* n = new testinfo;
    n->file=file;
    n->line=line;
    n->msg=msg;
    n->expression=expression;
    n->pass=pass;
    //messages->add(n);

    if(testH ==NULL){
      testH = n;
    }else{
      testinfo* temp;
      temp=testH;
      while(temp->next!=NULL){
        temp=temp->next;
      }
      temp->next=n;

    }



    failureInfo* f = new failureInfo;
    f->current_file=tt_current_file;
    f->current_line=tt_current_line;
    //f->name=name;
    f->current_msg=tt_current_msg;
    f->current_expression=tt_current_expression;
      f->name=tt_current_name;
    f->next=NULL;
    //failures->add(f);


    if(failureInfoH ==NULL){
      failureInfoH = f;
    }else{
      failureInfo* temp2;
      temp2=failureInfoH;
      while(temp2->next!=NULL){
        temp2=temp2->next;
      }
      temp2->next=f;

    }

  }

  return pass;
}




int tt_report(void)
{
  int i;
  /*for(i=0;i<=messages->length();i++){
    //printf("%d\n",messages->get(i)->line);
    printf("%c%sFAILED%c%s [%s] (passed:%d, failed:%d, total:%d)\n",
           TT_COLOR_CODE, TT_COLOR_RED, TT_COLOR_CODE, TT_COLOR_RESET,
           messages->get(i)->file, tt_passes, messages->length()+1, tt_passes + messages->length()+1);
  }
  */
  /*
  for(i=0;i<=failures->length();i++){
    failureInfo f = *failures->get(i);
    printf("failure: %s:%d: In test %s():\n    %s (%s)\n",
           f.current_file, f.current_line, f.name, f.current_msg, f.current_expression);
  }
   */
  failureInfo* f = failureInfoH;
  while(f != NULL) {
    printf("failure: %s:%d: In test %s():\n    %s (%s)\n",
           f->current_file, f->current_line, f->name, f->current_msg, f->current_expression);
    f=f->next;

  }

    printf("\n");

  if (tt_fails) {
    printf("%c%sFAILED%c%s [%s] (passed:%d, failed:%d, total:%d)\n",
      TT_COLOR_CODE, TT_COLOR_RED, TT_COLOR_CODE, TT_COLOR_RESET,
      tt_current_file, tt_passes, tt_fails, tt_passes + tt_fails);
    return -1;
  } else {
    printf("%c%sPASSED%c%s [%s] (total:%d)\n",
      TT_COLOR_CODE, TT_COLOR_GREEN, TT_COLOR_CODE, TT_COLOR_RESET,
      tt_current_file, tt_passes);
    return 0;
  }
}

#endif
