#include <iostream>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include "test.pb.h"
using namespace std;


//g++ test.cpp test.pb.cc -pthread -lprotobuf -g
int main() {
  OuterTest::InnerTest::TestMessage T;
  T.set_int_member(12);
  cout << T.string_member() << endl;
  cout << T.DebugString() << endl;
  cout << T.GetDescriptor()->DebugString() << endl;

  
  google::protobuf::compiler::DiskSourceTree sourceTree;  
  sourceTree.MapPath("path","../");
  google::protobuf::compiler::Importer importer(&sourceTree, NULL);
  importer.Import("path/import.proto");
  auto descriptor1 = importer.pool()->FindMessageTypeByName("T.ImportTest");
  cout << descriptor1->DebugString() << endl;
  google::protobuf::DynamicMessageFactory factory;
  auto proto1 = factory.GetPrototype(descriptor1);
  auto message1= proto1->New();
  auto reflection1 = message1->GetReflection();
  auto field1 = descriptor1->FindFieldByName("id");
  auto field2 = descriptor1->FindFieldByName("password");
  
  reflection1->SetString(message1, field1, "myid");
  reflection1->SetString(message1, field2, "password");

  cout << message1->DebugString() << endl;

  delete message1;

  return 0;
}