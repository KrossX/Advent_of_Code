/* Copyright (c) 2019 KrossX <krossx@live.com>
 * License: http://www.opensource.org/licenses/mit-license.html  MIT License
 */

//L 1
//R 2
//U 3
//D 4

int input_a[] = {2,1004,3,520,2,137,4,262,1,403,3,857,2,50,3,679,2,788,4,98,1,717,4,1,2,367,3,608,1,125,3,703,1,562,4,701,1,718,3,357,2,742,4,860,2,557,4,117,2,950,3,546,1,506,3,836,2,951,4,460,1,38,3,893,1,1,4,217,2,262,4,950,2,239,3,384,2,971,4,289,2,323,3,878,1,525,3,687,1,831,3,523,2,94,4,33,1,879,4,318,2,633,4,775,2,879,4,351,1,120,4,8,2,31,3,49,2,328,4,598,1,380,4,160,2,261,4,716,2,459,3,533,1,444,3,412,1,326,3,93,1,193,4,621,2,236,3,769,1,319,4,885,1,559,3,509,1,62,3,321,1,667,4,505,2,556,3,159,1,5,3,126,1,262,4,946,1,168,3,491,1,56,4,831,2,926,3,926,2,562,4,270,2,785,3,436,2,852,4,629,2,872,3,716,2,549,3,435,2,462,3,191,2,318,3,91,1,637,4,682,2,647,4,53,1,789,4,725,2,312,4,366,1,287,3,29,2,85,4,657,2,88,3,300,2,795,3,378,2,800,4,391,1,594,3,791,2,205,3,352,1,510,4,975,2,47,4,311,2,319,3,579,2,214,4,112,2,996,3,874,2,328,4,578,2,37,3,689,1,543,3,16,1,580,4,230,1,714,4,58,1,580,4,658,2,218,3,535,2,149,3,996,1,173,4,316,1,90,4,372,1,364,3,700,1,60,4,70,1,250,3,276,2,580,3,505,1,682,3,943,2,336,3,847,2,810,3,963,2,874,4,740,2,732,4,328,2,926,4,447,2,638,4,102,2,696,3,211,1,594,4,354,2,384,3,81,1,884,3,916,1,168,3,759,2,631,4,702,1,598,4,382,1,647,3,642,2,537,3,53,2,897,3,954,2,263,3,445,1,41,4,91,1,51,4,338,2,219,3,269,1,689,4,172,2,627,4,287,1,440,4,504,1,253,4,252,2,815,4,108,1,282,3,835,1,243,3,638,2,910,4,306,2,755,4,202,2,69,4,862,1,537,4,947,1,180,4,835,1,111,3,832,2,939,4,449,2,180,3,105,2,892,4,837,1,153,3,215,1,695,3,957,2,923,3,496,2,608,3,739,1,711,3,700,1,838,4,117,2,479,3,852,2,795,4,955,1,386,4,70,2,728,4,40,2,580,3,777,1,877,3,284,2,414,4,300,2,105,4,372,1,317,4,91,2,653,3,920,2,956,4,496,1,543,4,363,2,374,4,283,1,696,3,466,2,467,4,878,2,660,3,590,1,962,3,619,2,991,3,848,1,648,4,191,2,459,3,125,1,998,3,19,1,214,3,947,2,188,3,103,2,916,0,0};
int input_b[] = {1,1008,3,717,2,288,4,770,2,270,3,514,2,109,4,538,1,719,3,179,2,466,4,792,2,421,3,723,1,22,3,705,1,284,3,14,1,478,3,367,2,727,3,880,2,620,4,46,2,377,3,897,1,731,3,840,1,910,4,385,1,257,3,311,1,596,4,991,1,668,4,730,1,707,4,816,2,47,3,948,2,84,4,700,2,299,3,707,2,261,4,928,2,358,4,504,2,309,3,369,2,931,3,20,1,940,3,326,1,362,4,52,2,98,4,475,1,907,4,918,2,931,4,468,2,279,4,586,2,592,3,973,2,753,4,365,2,694,3,278,2,934,3,712,2,441,3,996,1,989,4,693,1,211,4,561,2,105,4,425,2,53,3,168,1,451,3,865,1,585,4,412,1,857,3,988,2,724,3,774,2,295,3,588,2,329,4,810,1,698,4,118,2,277,3,193,2,309,3,933,2,186,4,535,2,409,3,322,1,849,3,606,2,590,3,892,1,542,4,237,2,475,4,920,2,679,3,602,1,477,4,634,1,988,4,540,1,323,3,791,1,375,3,625,1,621,3,567,1,943,3,512,1,239,4,90,1,66,3,151,2,83,3,435,2,612,4,865,1,177,3,368,2,326,3,574,1,241,3,197,2,499,3,419,2,297,3,207,1,311,4,243,1,559,4,281,2,513,3,748,1,884,3,207,2,71,4,441,2,133,4,993,1,4,4,977,1,669,3,523,1,564,3,186,2,477,3,737,1,685,3,338,1,456,3,939,2,774,3,674,1,97,4,827,2,237,4,451,2,618,4,143,2,750,3,196,1,559,4,178,1,693,4,916,2,334,3,231,1,651,3,249,2,620,3,283,1,387,3,352,1,915,3,959,1,693,3,909,2,320,3,119,1,617,3,177,1,993,4,265,2,667,3,204,2,59,4,601,1,579,3,483,2,155,4,484,1,44,4,751,2,915,3,510,1,552,3,308,2,505,3,394,2,585,3,872,1,617,3,202,2,928,3,941,2,235,3,768,2,666,4,547,1,244,4,270,2,353,4,612,2,384,3,430,1,685,4,536,2,103,3,147,2,794,4,621,1,52,3,96,1,557,4,455,1,635,4,58,2,265,3,545,2,938,4,266,1,173,3,746,1,672,4,237,2,286,3,131,2,487,3,837,2,394,4,702,2,49,3,579,1,699,3,819,1,448,4,223,1,982,4,906,1,397,3,807,1,737,4,223,1,791,4,965,2,436,3,29,2,908,4,273,2,194,3,91,2,232,3,591,1,336,4,70,2,467,3,505,1,341,3,989,2,278,3,387,1,442,3,950,2,487,4,384,1,534,4,514,1,433,3,627,2,381,3,54,1,847,3,231,1,590,0,0};

int test1_a[] = {2,75,4,30,2,83,3,83,1,12,4,49,2,71,3,7,1,72,0,0};
int test1_b[] = {3,62,2,66,3,55,2,34,4,71,2,55,4,58,2,83,0,0};

int test2_a[] = {2,98,3,47,2,26,4,63,2,33,3,87,1,62,4,20,2,33,3,53,2,51,0,0};
int test2_b[] = {3,98,2,91,4,20,2,16,4,67,2,40,3,7,2,15,3,6,2,7,0,0};