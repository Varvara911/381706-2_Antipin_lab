#include "Text.h"

TText::TText(const char* string)
{
  root = new TTree(0);
  root->SetNextLevel(new TTree(1));
  root->GetNextLevel()->SetNextLevel(new TTree(string));
}

TText::TText(TText& text)
{
  root = text.Clone();
}

void TText::Insert(const int pos, const char* string)
{
  int string_len = strlen(string);
  TTree* str = new TTree(string[0]);
  TTree* start_str = str;
  int i = 1;
  for (i; i < string_len; i++)
  {
    str->SetSameLevel(new TTree(string[i]));
    str = str->GetSameLevel();
  }
  TStackList<TTree*> stack;
  stack.Put(root);
  int len = 0;
  while (len != pos - 1)
  {
    TTree* tmp = stack.Get();
    if (tmp->GetLevel() == 3)
      len++;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  TTree* point = stack.Get();
  str->SetSameLevel(point->GetSameLevel());
  point->SetSameLevel(start_str);
}

void TText::Insert(TTree* start, TTree* string)
{
  TTree* tmp1 = string;
  TTree* tmp2 = root;
  while (tmp2->GetLevel() != start->GetLevel())
    tmp2 = tmp2->GetNextLevel();
  while (tmp2 != start)
    tmp2 = tmp2->GetSameLevel();
  tmp1->SetSameLevel(tmp2->GetSameLevel());
  tmp2->SetSameLevel(tmp1);
}

int TText::Find(const char* string)
{
  TStackList<TTree*> stack;
  stack.Put(root);
  int len = strlen(string);
  int i = 0;//��������
  int pos = 0;//�������
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp->GetLetter() == string[i])
      i++;
    else if (tmp->GetLevel() == 3 && tmp->GetLetter() != string[i])
    {
      if (i != 0)
      {
        stack.Put(tmp);
        pos += i;
        i = 0;
      }
      else
        pos++;
    }
    if (i == len)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  return pos;
}

TTree* TText::FindTree(const char* string)
{
  TStackList<TTree*> stack;
  stack.Put(root);
  TTree* res = NULL;
  int len = strlen(string);
  int i = 0;//��������
  int pos = 0;//�������
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp->GetLetter() == string[i])
    {
      if (i == 0)
        res = tmp;
      i++;
    }
    else if (tmp->GetLevel() == 3 && tmp->GetLetter() != string[i])
    {
      if (i != 0)
      {
        stack.Put(tmp);
        res = NULL;
        i = 0;
      }
    }
    if (i == len)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  return res;
}

char* TText::Copy(const int start, const int len)
{
  char* res;
  TStackList<TTree*> stack;
  stack.Put(root);
  //TTree* res = NULL;
  int i = 0;//��������
  int pos = 0;//�������
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp->GetLevel() == 3)
      pos++;
    else if (tmp->GetLevel() == 3 && pos == start + i)
    {
      pos++;
      res[i] = tmp->GetLetter();
      i++;
    }
    if (i == len)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  return res;
}

TTree* TText::Copy(TTree* start, const int len)
{
  TTree* res = new TTree(0);
  TTree* res_s = new TTree(1);
  TTree* res_w = new TTree(*start);
  res->SetNextLevel(res_s);
  res_s->SetNextLevel(res_w);
  TStackList<TTree*> stack;
  stack.Put(root);
  int i = len;//��������
  bool flag = false;
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp == start)
    {
      //res_s->SetNextLevel(tmp);
      i--;
      flag = true;
    }
    else if (flag == true && tmp->GetLevel() == 3)
    {
      res_w->SetSameLevel(new TTree(*tmp));
      res_w = res_w->GetSameLevel();
      i--;
    }
    if (i == 0)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  return res;
}

void TText::Delete(const int start_del, const int lenght)
{
  TStackList<TTree*> stack;
  stack.Put(root);
  int i = 0;//��������
  int pos = 0;//�������
  TTree* temp1;
  TTree* temp2;
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp->GetLevel() == 3 && pos == start_del - 1)
      temp1 = tmp;
    if (tmp->GetLevel() == 3)
      pos++;
    else if (tmp->GetLevel() == 3 && pos == start_del + i)
    {
      TTree* tmp_1 = tmp;
      if (i == lenght - 1)
        temp2 = tmp->GetSameLevel();
      delete tmp_1;
      pos++;
      i++;
    }
    if (i == lenght)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  temp1->SetSameLevel(temp2);
}

void TText::Delete(TTree* start_del, const int lenght)
{
  TStackList<TTree*> stack;
  stack.Put(root);
  int i = lenght;//��������
  bool flag = false;
  TTree* temp1;
  TTree* temp2;
  while (stack.IsEmpty())
  {
    TTree* tmp = stack.Get();
    if (tmp->GetSameLevel() == start_del)
      temp1 = tmp;
    if (tmp == start_del)
    {
      TTree* tmp_1 = tmp;
      delete tmp_1;
      i--;
      flag = true;
    }
    else if (flag == true && tmp->GetLevel() == 3)
    {
      TTree* tmp_1 = tmp;
      if (i == 1)
        temp2 = tmp->GetSameLevel();
      delete tmp_1;
      i--;
    }
    if (i == 0)
      break;
    if (tmp->GetSameLevel() != NULL)
      stack.Put(tmp->GetSameLevel());
    if (tmp->GetNextLevel() != NULL)
      stack.Put(tmp->GetNextLevel());
  }
  temp1->SetSameLevel(temp2);
}