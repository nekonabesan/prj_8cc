// テストケース記述ファイル
#include "gtest/gtest.h" // googleTestを使用するおまじないはこれだけでOK
// テスト対象関数を呼び出せるようにするのだが
// extern "C"がないとCと解釈されない、意外とハマりがち。
extern "C" {
  #include "../8cc_main_target.h"
}

// fixtureNameはテストケース群をまとめるグループ名と考えればよい、任意の文字列
// それ以外のclass～testing::Testまではおまじないと考える
class fixtureName : public ::testing::Test {
protected:
    // fixtureNameでグループ化されたテストケースはそれぞれのテストケース実行前に
    // この関数を呼ぶ。共通の初期化処理を入れておくとテストコードがすっきりする
    virtual void SetUp(){
    }
    // SetUpと同様にテストケース実行後に呼ばれる関数。共通後始末を記述する。
    virtual void TearDown(){
    }
};

// 成功するテストケース。細かい説明はGoogleTestのマニュアルを見てね。
/*TEST_F(fixtureName, sample)
{
  //initialize では先のアルゴリズムによって roomprice を順に初期化しています
  //int *roomprice = (int *)malloc(rmax * sizeof(int));
  //int *roomsel = (int *)malloc(rmax * sizeof(int));
}*/


//============================================================================//
// b. quick error 01
//============================================================================//
TEST_F(fixtureName, error)
{
  // 値を読み出す時には room1 という下請け関数を呼びます。
  // この関数は、人数 i が負のときは 0 を返し、それ以外はroomprice[i] を返します。
  /*int n = 8;
  int *a = (int *)malloc(n * sizeof(int));
  int left = 0;
  a[0] = 55;
  a[1] = 13;
  a[2] = 3;
  a[3] = 45;
  a[4] = 74;
  a[5] = 87;
  a[6] = 46;
  a[7] = 30;
  msort(a, left, n);
  EXPECT_EQ(a[0], 3);
  EXPECT_EQ(a[1], 13);
  EXPECT_EQ(a[2], 30);
  EXPECT_EQ(a[3], 45);
  EXPECT_EQ(a[4], 46);
  EXPECT_EQ(a[5], 55);
  EXPECT_EQ(a[6], 74);
  EXPECT_EQ(a[7], 87);
  free(a);*/
}

//============================================================================//
// c. quick consume 01
//============================================================================//
TEST_F(fixtureName, consume)
{

}

//============================================================================//
// c. quick expect_number 01
//============================================================================//
TEST_F(fixtureName, expect_number)
{

}

//============================================================================//
// c. quick at_eof 01
//============================================================================//
TEST_F(fixtureName, at_eof)
{

}

//============================================================================//
// c. quick new_token 01
//============================================================================//
TEST_F(fixtureName, new_token)
{

}

//============================================================================//
// c. quick new_token 01
//============================================================================//
TEST_F(fixtureName, tokenize)
{
  Token *tk;
  Token *hd;
  char *p = (char *)malloc(14 * sizeof(char));
  p[0] = ' ';
  p[1] = '1';
  p[2] = '2';
  p[3] = ' ';
  p[4] = '+';
  p[5] = ' ';
  p[6] = '3';
  p[7] = '4';
  p[8] = ' ';
  p[9] = '-';
  p[10] = ' ';
  p[11] = '5';
  p[12] = ' ';
  p[13] = '\0';
  // case 01
  hd = tokenize(p);
  EXPECT_EQ(hd->val, 12);
  EXPECT_EQ(hd->kind, TK_NUM);
  ASSERT_STREQ(hd->str, "12 + 34 - 5 ");
  hd = hd->next;
  EXPECT_EQ(hd->val, 0);
  EXPECT_EQ(hd->kind, TK_RESERVED);
  ASSERT_STREQ(hd->str, "+ 34 - 5 ");
  hd = hd->next;
  EXPECT_EQ(hd->val, 34);
  EXPECT_EQ(hd->kind, TK_NUM);
  ASSERT_STREQ(hd->str, "34 - 5 ");
  hd = hd->next;
  EXPECT_EQ(hd->val, 0);
  EXPECT_EQ(hd->kind, TK_RESERVED);
  ASSERT_STREQ(hd->str, "- 5 ");
  hd = hd->next;
  EXPECT_EQ(hd->val, 5);
  ASSERT_STREQ(hd->str, "5 ");
  EXPECT_EQ(hd->kind, TK_NUM);
  hd = hd->next;
  EXPECT_EQ(hd->val, 0);
  EXPECT_EQ(hd->kind, TK_EOF);
  // free
  free(p);
}
