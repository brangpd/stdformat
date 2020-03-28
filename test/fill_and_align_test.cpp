#include "testutil.h"

struct FillAndAlignTest : FormatTest {};

TEST_F(FillAndAlignTest, FillAlignShiftTest_Decimal_Test) {
  EXPECT_EQ(format("{:10}", 42), "        42");
  EXPECT_EQ(format("{:`>10}", 42), "````````42");
  EXPECT_EQ(format("{:`<10}", 42), "42````````");
  EXPECT_EQ(format("{:`^10}", 42), "````42````");
  EXPECT_EQ(format("{:`^11}", 42), "````42`````");
  EXPECT_EQ(format("{:`>11}", 42), "`````````42");
  EXPECT_EQ(format("{:`<11}", 42), "42`````````");

  EXPECT_EQ(format("{:10}", -42), "       -42");
  EXPECT_EQ(format("{:`>10}", -42), "```````-42");
  EXPECT_EQ(format("{:`<10}", -42), "-42```````");
  EXPECT_EQ(format("{:`^10}", -42), "```-42````");
  EXPECT_EQ(format("{:`^11}", -42), "````-42````");
  EXPECT_EQ(format("{:`>11}", -42), "````````-42");
  EXPECT_EQ(format("{:`<11}", -42), "-42````````");
}

TEST_F(FillAndAlignTest, FillAlignShiftTest_Hexadecimal_Test) {
  EXPECT_EQ(format("{:10x}", -0x2a), "       -2a");
  EXPECT_EQ(format("{:`>10x}", -0x2a), "```````-2a");
  EXPECT_EQ(format("{:`<10x}", -0x2a), "-2a```````");
  EXPECT_EQ(format("{:`^10x}", -0x2a), "```-2a````");
  EXPECT_EQ(format("{:`^11x}", -0x2a), "````-2a````");
  EXPECT_EQ(format("{:`>11x}", -0x2a), "````````-2a");
  EXPECT_EQ(format("{:`<11x}", -0x2a), "-2a````````");

  EXPECT_EQ(format("{:#10X}", -0x2a), "     -0X2A");
  EXPECT_EQ(format("{:`>#10X}", -0x2a), "`````-0X2A");
  EXPECT_EQ(format("{:`<#10X}", -0x2a), "-0X2A`````");
  EXPECT_EQ(format("{:`^#10X}", -0x2a), "``-0X2A```");
  EXPECT_EQ(format("{:`^#11X}", -0x2a), "```-0X2A```");
  EXPECT_EQ(format("{:`>#11X}", -0x2a), "``````-0X2A");
  EXPECT_EQ(format("{:`<#11X}", -0x2a), "-0X2A``````");

  EXPECT_EQ(format("{: #10X}", 0x2a), "      0X2A");
  EXPECT_EQ(format("{:`> #10X}", 0x2a), "````` 0X2A");
  EXPECT_EQ(format("{:`< #10X}", 0x2a), " 0X2A`````");
  EXPECT_EQ(format("{:`^ #10X}", 0x2a), "`` 0X2A```");
  EXPECT_EQ(format("{:`^ #11X}", 0x2a), "``` 0X2A```");
  EXPECT_EQ(format("{:`> #11X}", 0x2a), "`````` 0X2A");
  EXPECT_EQ(format("{:`< #11X}", 0x2a), " 0X2A``````");

  EXPECT_EQ(format("{:+#10X}", 0x2a), "     +0X2A");
  EXPECT_EQ(format("{:`>+#10X}", 0x2a), "`````+0X2A");
  EXPECT_EQ(format("{:`<+#10X}", 0x2a), "+0X2A`````");
  EXPECT_EQ(format("{:`^+#10X}", 0x2a), "``+0X2A```");
  EXPECT_EQ(format("{:`^+#11X}", 0x2a), "```+0X2A```");
  EXPECT_EQ(format("{:`>+#11X}", 0x2a), "``````+0X2A");
  EXPECT_EQ(format("{:`<+#11X}", 0x2a), "+0X2A``````");
}

TEST_F(FillAndAlignTest, FillAlignShiftTest_Binary_Test) {
  EXPECT_EQ(format("{:#10b}", -0b1010), "   -0b1010");
  EXPECT_EQ(format("{:`>#10b}", -0b1010), "```-0b1010");
  EXPECT_EQ(format("{:`<#10b}", -0b1010), "-0b1010```");
  EXPECT_EQ(format("{:`^#10b}", -0b1010), "`-0b1010``");
  EXPECT_EQ(format("{:`^#11b}", -0b1010), "``-0b1010``");
  EXPECT_EQ(format("{:`>#11b}", -0b1010), "````-0b1010");
  EXPECT_EQ(format("{:`<#11b}", -0b1010), "-0b1010````");

  EXPECT_EQ(format("{: #10B}", 0b1010), "    0B1010");
  EXPECT_EQ(format("{:`> #10B}", 0b1010), "``` 0B1010");
  EXPECT_EQ(format("{:`< #10B}", 0b1010), " 0B1010```");
  EXPECT_EQ(format("{:`^ #10B}", 0b1010), "` 0B1010``");
  EXPECT_EQ(format("{:`^ #11B}", 0b1010), "`` 0B1010``");
  EXPECT_EQ(format("{:`> #11B}", 0b1010), "```` 0B1010");
  EXPECT_EQ(format("{:`< #11B}", 0b1010), " 0B1010````");
}

TEST_F(FillAndAlignTest, FillAlignShiftTest_Octal_Test) {
  // 0 should never be 00
  EXPECT_EQ(format("{:10o}", 00), "         0");
  EXPECT_EQ(format("{:`>10o}", 00), "`````````0");
  EXPECT_EQ(format("{:`<10o}", 00), "0`````````");
  EXPECT_EQ(format("{:`^10o}", 00), "````0`````");
  EXPECT_EQ(format("{:`^11o}", 00), "`````0`````");
  EXPECT_EQ(format("{:`>11o}", 00), "``````````0");
  EXPECT_EQ(format("{:`<11o}", 00), "0``````````");

  EXPECT_EQ(format("{:#10o}", 00), "         0");
  EXPECT_EQ(format("{:`>#10o}", 00), "`````````0");
  EXPECT_EQ(format("{:`<#10o}", 00), "0`````````");
  EXPECT_EQ(format("{:`^#10o}", 00), "````0`````");
  EXPECT_EQ(format("{:`^#11o}", 00), "`````0`````");
  EXPECT_EQ(format("{:`>#11o}", 00), "``````````0");
  EXPECT_EQ(format("{:`<#11o}", 00), "0``````````");

  EXPECT_EQ(format("{:10o}", 01234), "      1234");
  EXPECT_EQ(format("{:`>10o}", 01234), "``````1234");
  EXPECT_EQ(format("{:`<10o}", 01234), "1234``````");
  EXPECT_EQ(format("{:`^10o}", 01234), "```1234```");
  EXPECT_EQ(format("{:`^11o}", 01234), "```1234````");
  EXPECT_EQ(format("{:`>11o}", 01234), "```````1234");
  EXPECT_EQ(format("{:`<11o}", 01234), "1234```````");

  EXPECT_EQ(format("{:+10o}", 00), "        +0");
  EXPECT_EQ(format("{:`>+10o}", 00), "````````+0");
  EXPECT_EQ(format("{:`<+10o}", 00), "+0````````");
  EXPECT_EQ(format("{:`^+10o}", 00), "````+0````");
  EXPECT_EQ(format("{:`^+11o}", 00), "````+0`````");
  EXPECT_EQ(format("{:`>+11o}", 00), "`````````+0");
  EXPECT_EQ(format("{:`<+11o}", 00), "+0`````````");

  EXPECT_EQ(format("{:#10o}", 01234), "     01234");
  EXPECT_EQ(format("{:`>#10o}", 01234), "`````01234");
  EXPECT_EQ(format("{:`<#10o}", 01234), "01234`````");
  EXPECT_EQ(format("{:`^#10o}", 01234), "``01234```");
  EXPECT_EQ(format("{:`^#11o}", 01234), "```01234```");
  EXPECT_EQ(format("{:`>#11o}", 01234), "``````01234");
  EXPECT_EQ(format("{:`<#11o}", 01234), "01234``````");
}

TEST_F(FillAndAlignTest, FillAlignShiftTest_String_Test) {
  // default alignment is right, default fill char is space
  EXPECT_EQ(format("{:10}", "hello"), "hello     ");
  EXPECT_EQ(format("{:`>}", "hello"), "hello");

  EXPECT_EQ(format("{:`>10}", "hello"), "`````hello");
  EXPECT_EQ(format("{:`<10}", "hello"), "hello`````");
  EXPECT_EQ(format("{:`^10}", "hello"), "``hello```");
  EXPECT_EQ(format("{:`>11}", "hello"), "``````hello");
  EXPECT_EQ(format("{:`<11}", "hello"), "hello``````");
  EXPECT_EQ(format("{:`^11}", "hello"), "```hello```");
}

TEST_F(FillAndAlignTest, FillAlignShiftTest_FullWidthCharacter_Test) {
  EXPECT_EQ(format("{}{}", "你好", "世界"), "你好世界");
  EXPECT_EQ(format("{}{}", "字符串OK", "字符串"), "字符串OK字符串");
  EXPECT_EQ(format("{:`^4}", "全角"), "全角");
  EXPECT_EQ(format("{:`<4}", "全角"), "全角");
  EXPECT_EQ(format("{:`>4}", "全角"), "全角");
  EXPECT_EQ(format("{:`^6}", "全角"), "`全角`");
  EXPECT_EQ(format("{:`<6}", "全角"), "全角``");
  EXPECT_EQ(format("{:`>6}", "全角"), "``全角");
  EXPECT_EQ(format("{:`^5}", "全角"), "全角`");
  EXPECT_EQ(format("{:`<5}", "全角"), "全角`");
  EXPECT_EQ(format("{:`>5}", "全角"), "`全角");
}
