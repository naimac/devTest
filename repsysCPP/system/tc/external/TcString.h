#ifndef _TCTESTRING_H
#define _TCTESTRING_H

#include <string.h>
#include <stdio.h>
#include "TcClient/TcClientDefinitions.h" // für TcDirEntryKind

class CString {
public:
   // Basisoperationen
   CString();
   CString(const char* str);
   explicit CString(const CString &cs);
   CString(const void *p, ...);
   ~CString();

   CString& operator= (const CString &s);
   CString& operator= (const char* p);
   CString& operator<< (const char* p);
   bool operator== (const char* p);
   bool operator!= (const char* p);
   operator const char * const () const { return mpBuf; }

   const char *Get() const { return mpBuf; }
   int GetLen() const { return mLen; }
   CString& Set(const char* b) { Set(b, 0, strlen(b)); return *this; }

   // mehrzeilige Operationen
   int GetMaxLen() const;
   CString AddLeft(const char *head);
   CString AddRight(const char *tail);
   CString TrimLeft();
   CString TrimRight();
   CString Trim();
   CString Indent(int ind) const;
   CString Divide(int div);
   CString Block(int len);

   // in-place Manipulation
   CString    &RmvEnd(char c);
   CString    &RmvExt();
   CString    &RmvTail();
   const char *GetEnd(char c);
   const char *GetExt();
   const char *GetTail();
   CString    &ChangeChar(char oldChar, char newChar);
   CString    &Trunc(char c);
   CString    &ToLower();

   // diverses
   CString    &AddTail(const char* s);
   CString &AdjustSlash();

   CString& CatMessage (const char *msg, const char *add);
   bool IsEmpty() const;
   char* Replace(const char* p, int nr, const char* r);
   CString ReplaceEsc();

   inline bool IterString(char **ppBeg, char **ppEnd, const char *pSplit, int *cnt) {
      if (!(**ppBeg)) return false;
      while (**ppBeg && strchr(pSplit, **ppBeg)) {
         (*ppBeg)++;
         (*cnt)++;
      }
      *ppEnd = *ppBeg + strcspn(*ppBeg, pSplit);
      return true;
   }

   //void ConvertSpecialChars(bool toRealPath = true);
   void Insert(const char *pString, int beg, int end);
   void Setf(const char *pString, ...);

   // Static
   static CString GetIndent (int ind, char c = ' ');

private:
   char *mpBuf; // Stringbuffer
   int   mLen;  // Anzahl der Zeichen im String
   int   mSize; // Anzahl der Zeichen die höchstens Platz haben

   void Init(const char *s = 0);
   void Set(const char* b, int i, int j);
   void Redim(int nl);

   void MoveLeft(int beg, int cnt);
   void MoveRight(int beg, int cnt);

   // verhindern von Fehlverwendungen
   CString operator+ (char);
   CString& operator+= (const char* a);
};

#endif
