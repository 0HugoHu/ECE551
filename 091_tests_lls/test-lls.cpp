#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

#define TEST_NUM1 1564325
#define TEST_NUM2 9516423
#define TEST_NUM3 5461984

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(TEST_NUM1);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == NULL);
    assert(il.tail->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM1 && il.head == il.tail);
    assert(il.getSize() == 1 && il[0] == TEST_NUM1);

    il.addFront(TEST_NUM2);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == il.tail);
    assert(il.tail->prev == il.head && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM2 && il.tail->data == TEST_NUM1);
    assert(il.getSize() == 2 && il[0] == TEST_NUM2 && il[1] == TEST_NUM1);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(TEST_NUM1);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == NULL);
    assert(il.tail->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM1 && il.head == il.tail);
    assert(il.getSize() == 1 && il[0] == TEST_NUM1);

    il.addBack(TEST_NUM2);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == il.tail);
    assert(il.tail->prev == il.head && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM1 && il.tail->data == TEST_NUM2);
    assert(il.getSize() == 2 && il[0] == TEST_NUM1 && il[1] == TEST_NUM2);
  }

  void testAssignCopy() {
    IntList * il1 = new IntList();
    il1->addFront(TEST_NUM2);
    il1->addBack(TEST_NUM3);
    il1->addFront(TEST_NUM1);

    IntList * il2 = new IntList();
    *il2 = *il1;

    il1->addFront(TEST_NUM1);

    // 123
    assert(il2->head != NULL && il2->tail != NULL);
    assert(il2->head->prev == NULL && il2->head->next->data == TEST_NUM2 &&
           il2->head->next->next->data == TEST_NUM3);
    assert(il2->head->next->prev->data == TEST_NUM1 &&
           il2->head->next->next == il2->tail);
    assert(il2->tail->prev->data == TEST_NUM2 &&
           il2->tail->prev->prev->data == TEST_NUM1 && il2->tail->next == NULL);
    assert(il2->head->data == TEST_NUM1 && il2->tail->data == TEST_NUM3);
    assert(il2->getSize() == 3 && (*il2)[0] == TEST_NUM1 && (*il2)[1] == TEST_NUM2 &&
           (*il2)[2] == TEST_NUM3);

    IntList * il3 = new IntList(*il1);
    // 1123
    assert(il3->head != NULL && il3->tail != NULL);
    assert(il3->head->prev == NULL && il3->head->next->data == TEST_NUM1 &&
           il3->head->next->next->data == TEST_NUM2 &&
           il3->head->next->next->next->data == TEST_NUM3);
    assert(il3->head->next->prev->data == TEST_NUM1 &&
           il3->head->next->next == il3->tail->prev);
    assert(il3->tail->prev->data == TEST_NUM2 &&
           il3->tail->prev->prev->data == TEST_NUM1 &&
           il3->tail->prev->prev->prev->data == TEST_NUM1 && il3->tail->next == NULL);
    assert(il3->head->data == TEST_NUM1 && il3->tail->data == TEST_NUM3);
    assert(il3->getSize() == 4 && (*il3)[0] == TEST_NUM1 && (*il3)[1] == TEST_NUM1 &&
           (*il3)[2] == TEST_NUM2 && (*il3)[3] == TEST_NUM3);

    il1->addFront(TEST_NUM1);

    assert(il1->getSize() == 5 && il2->getSize() == 3 && il3->getSize() == 4);

    il2->remove(TEST_NUM3);
    //12
    assert(il2->head != NULL && il2->tail != NULL);
    assert(il2->head->prev == NULL && il2->head->next->data == TEST_NUM2 &&
           il2->head->next->next == NULL);
    assert(il2->head->next->prev->data == TEST_NUM1 && il2->head->next == il2->tail);
    assert(il2->tail->prev->data == TEST_NUM1 && il2->tail->prev->prev == NULL &&
           il2->tail->next == NULL);
    assert(il2->head->data == TEST_NUM1 && il2->tail->data == TEST_NUM2);
    assert(il2->getSize() == 2 && (*il2)[0] == TEST_NUM1 && (*il2)[1] == TEST_NUM2);

    delete (il1);
    assert(il2->getSize() == 2 && il3->getSize() == 4);
    delete (il2);
    assert(il3->getSize() == 4);
    delete (il3);

    IntList * il4 = new IntList();
    assert(il4->getSize() == 0 && il4->head == NULL && il4->tail == NULL);
    IntList * il5 = new IntList();
    *il5 = *il4;
    assert(il5->getSize() == 0 && il5->head == NULL && il5->tail == NULL);
    il4->addFront(TEST_NUM1);
    assert(il5->getSize() == 0 && il5->head == NULL && il5->tail == NULL);

    il5->addFront(TEST_NUM1);
    assert(il5->getSize() == 1 && il5->head->prev == NULL && il5->head->next == NULL &&
           il5->head == il5->tail && il5->head->data == TEST_NUM1);

    delete (il5);
    il4->remove(TEST_NUM1);
    IntList * il6 = new IntList(*il4);
    delete (il4);
    assert(il6->getSize() == 0 && il6->head == NULL && il6->tail == NULL);

    delete (il6);

    IntList il7;
    IntList il8;
    il8 = il7;
    assert(il8.getSize() == 0 && il8.head == NULL && il8.tail == NULL);
    il7.addBack(TEST_NUM1);
    il7.addFront(TEST_NUM3);
    //31
    IntList il9(il8);
    assert(il9.getSize() == 0 && il9.head == NULL && il9.tail == NULL);
    il9 = il7;
    assert(il9.getSize() == 2 && il9.head->prev == NULL && il9.head->next == il9.tail &&
           il9.head != il9.tail && il9.head->data == TEST_NUM3 &&
           il9.tail->data == TEST_NUM1);

    IntList * il10 = new IntList();
    il10->addFront(TEST_NUM1);
    IntList * il11 = new IntList(*il10);
    assert(il10->head != il11->head && il10->tail != il11->tail);
    delete il10;
    delete il11;
  }

  void testTest() {
    IntList il1;
    il1.addFront(TEST_NUM1);
    IntList il2;

    il2.addBack(TEST_NUM2);
    il2 = il1;
    assert(il2.getSize() == 1);
    assert(il2.head->data == TEST_NUM1 && il2.tail->data == TEST_NUM1);
    assert(il2.tail->next == NULL && il2.head->prev == NULL);

    assert(il1.head == il1.tail && il1.head->data == TEST_NUM1 && il1.head->prev == NULL &&
           il1.head->next == NULL && il1.getSize() == 1 && il1.find(TEST_NUM1) == 0 &&
           il1[0] == TEST_NUM1);

    il1.addBack(TEST_NUM2);
    il1.addBack(TEST_NUM3);
    il1.remove(TEST_NUM2);
    assert(il1.head->next == il1.tail && il1.head->data == TEST_NUM1 && il1.head->prev == NULL &&
           il1.tail->data == TEST_NUM3 && il1.tail->prev == il1.head && il1.tail->next == NULL &&
           il1.getSize() == 2 && il1.find(TEST_NUM1) == 0 && il1[0] == TEST_NUM1 && il1[1] == TEST_NUM3 &&
           il1.find(TEST_NUM3) == 1);

  }

  void testRemove() {
    IntList il;
    assert(il.remove(TEST_NUM1) == false);
    assert(il.head == NULL && il.tail == NULL);
    assert(il.getSize() == 0);

    il.addFront(TEST_NUM2);
    il.addBack(TEST_NUM3);
    il.addFront(TEST_NUM1);
    assert(il.remove(TEST_NUM1) == true);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == il.tail);
    assert(il.tail->prev == il.head && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM2 && il.tail->data == TEST_NUM3);
    assert(il.getSize() == 2);

    assert(il.remove(TEST_NUM1) == false);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == il.tail);
    assert(il.tail->prev == il.head && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM2 && il.tail->data == TEST_NUM3);
    assert(il.getSize() == 2);

    assert(il.remove(TEST_NUM3) == true);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->prev == NULL && il.head->next == NULL);
    assert(il.tail->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == TEST_NUM2 && il.head == il.tail);
    assert(il.getSize() == 1 && il[0] == TEST_NUM2);
    assert(il.find(TEST_NUM2) == 0);

    assert(il.remove(TEST_NUM2) == true);
    assert(il.head == NULL && il.tail == NULL);
    assert(il.getSize() == 0);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testAssignCopy();
  t.testRemove();
  t.testTest();
  return EXIT_SUCCESS;
}
