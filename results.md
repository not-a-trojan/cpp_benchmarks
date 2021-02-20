<details><summary>--- <b>Erasing From Containers</b> ---</summary>

<br/>

This benchmark explores the differences in removing the first/last/random element from various STL containers.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| 10'000 elements | clang++  | g++ 
|----------------:|-----:|-----:|
| erase random element from `std::vector<u64>` | 1.07 µs | 1.05 µs|
| erase first element from `std::vector<u64>` | 1.5294x | 1.5149x|
| erase last element from `std::vector<u64>` | 0.4018x | 0.5060x|
| erase random element from `std::list<u64>` | 0.7320x | 0.8930x|
| erase first element from `std::list<u64>` | 0.5392x | 0.4492x|
| erase last element from `std::list<u64>` | 0.4377x | 0.5183x|
| erase random element from `std::deque<u64>` | 1.1438x | 0.9834x|
| erase first element from `std::deque<u64>` | 0.4052x | 0.4672x|
| erase last element from `std::deque<u64>` | 0.5856x | 0.6340x|
| erase random element from `std::set<u64>` | 0.5882x | 0.4917x|
| erase first element from `std::set<u64>` | 0.5229x | 0.5209x|
| erase last element from `std::set<u64>` | 0.4964x | 0.5060x|
| erase random element from `std::unordered_set<u64>` | 0.5592x | 0.4912x|
| erase first element from `std::unordered_set<u64>` | 0.4964x | 0.5050x|
| erase last element from `std::unordered_set<u64>` | 0.3983x | 0.5050x|
| erase random element from `std::map<u64, u64>` | 0.5909x | 0.5183x|
| erase first element from `std::map<u64, u64>` | 0.5271x | 0.5793x|
| erase last element from `std::map<u64, u64>` | 0.5710x | 0.5714x|
| erase random element from `std::unordered_map<u64, u64>` | 0.5229x | 0.4338x|
| erase first element from `std::unordered_map<u64, u64>` | 0.5554x | 0.5050x|
| erase last element from `std::unordered_map<u64, u64>` | 0.5310x | 0.4239x|

<br/><br/>

| 100'000 elements | clang++  | g++ 
|-----------------:|-----:|-----:|
| erase random element from `std::vector<u64>` | 6.14 µs | 6.45 µs|
| erase first element from `std::vector<u64>` | 2.0909x | 2.0432x|
| erase last element from `std::vector<u64>` | 0.0955x | 0.0919x|
| erase random element from `std::list<u64>` | 0.1018x | 0.0000x|
| erase first element from `std::list<u64>` | 0.1114x | 0.0872x|
| erase last element from `std::list<u64>` | 0.0993x | 0.0859x|
| erase random element from `std::deque<u64>` | 1.1648x | 0.9946x|
| erase first element from `std::deque<u64>` | 0.0967x | 0.0848x|
| erase last element from `std::deque<u64>` | 0.0986x | 0.0930x|
| erase random element from `std::set<u64>` | 0.0886x | 0.1114x|
| erase first element from `std::set<u64>` | 0.0932x | 0.0775x|
| erase last element from `std::set<u64>` | 0.0865x | 0.0822x|
| erase random element from `std::unordered_set<u64>` | 0.0722x | 0.0908x|
| erase first element from `std::unordered_set<u64>` | 0.0891x | 0.0735x|
| erase last element from `std::unordered_set<u64>` | 0.0864x | 0.0908x|
| erase random element from `std::map<u64, u64>` | 0.0818x | 0.0822x|
| erase first element from `std::map<u64, u64>` | 0.0865x | 0.0788x|
| erase last element from `std::map<u64, u64>` | 0.0938x | 0.0673x|
| erase random element from `std::unordered_map<u64, u64>` | 0.0966x | 0.0714x|
| erase first element from `std::unordered_map<u64, u64>` | 0.0815x | 0.0814x|
| erase last element from `std::unordered_map<u64, u64>` | 0.0773x | 0.0670x|

<br/><br/>

| 1'000'000 elements | clang++  | g++ 
|-------------------:|-----:|-----:|
| erase random element from `std::vector<u64>` | 62.78 µs | 62.78 µs|
| erase first element from `std::vector<u64>` | 1.9056x | 2.0000x|
| erase last element from `std::vector<u64>` | 0.0067x | 0.0080x|
| erase random element from `std::list<u64>` | 0.0199x | 0.0199x|
| erase first element from `std::list<u64>` | 0.0087x | 0.0098x|
| erase last element from `std::list<u64>` | 0.0085x | 0.0095x|
| erase random element from `std::deque<u64>` | 1.0667x | 1.0000x|
| erase first element from `std::deque<u64>` | 0.0067x | 0.0081x|
| erase last element from `std::deque<u64>` | 0.0076x | 0.0092x|
| erase random element from `std::set<u64>` | 0.0106x | 0.0080x|
| erase first element from `std::set<u64>` | 0.0118x | 0.0082x|
| erase last element from `std::set<u64>` | 0.0084x | 0.0096x|
| erase random element from `std::unordered_set<u64>` | 0.0085x | 0.0098x|
| erase first element from `std::unordered_set<u64>` | 0.0087x | 0.0086x|
| erase last element from `std::unordered_set<u64>` | 0.0092x | 0.0091x|
| erase random element from `std::map<u64, u64>` | 0.0100x | 0.0092x|
| erase first element from `std::map<u64, u64>` | 0.0097x | 0.0090x|
| erase last element from `std::map<u64, u64>` | 0.0087x | 0.0082x|
| erase random element from `std::unordered_map<u64, u64>` | 0.0095x | 0.0092x|
| erase first element from `std::unordered_map<u64, u64>` | 0.0086x | 0.0098x|
| erase last element from `std::unordered_map<u64, u64>` | 0.0091x | 0.0085x|

<br/><br/>

</details>
<details><summary>--- <b>Filling Vector With And Without Reserve</b> ---</summary>

<br/>

This benchmark explores the differences in filling a `std::vector`, one element at a time, with and without using reserve().<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| pushing 10'000 values into a `std::vector<u64>` | clang++  | g++ 
|------------------------------------------------:|-----:|-----:|
| without reserve | 85.79 µs | 119.98 µs|
| with reserve | 0.2992x | 0.4884x|

<br/><br/>

| pushing 100'000 values into a `std::vector<u64>` | clang++  | g++ 
|-------------------------------------------------:|-----:|-----:|
| without reserve | 1.38 ms | 1.69 ms|
| with reserve | 0.1859x | 0.3634x|

<br/><br/>

| pushing 1'000'000 values into a `std::vector<u64>` | clang++  | g++ 
|---------------------------------------------------:|-----:|-----:|
| without reserve | 13.11 ms | 16.01 ms|
| with reserve | 0.1957x | 0.3661x|

<br/><br/>

</details>
<details><summary>--- <b>Iterating Containers</b> ---</summary>

<br/>

This benchmark explores the differences in iterating over various STL containers via reference and iterators.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| iterating over 10'000 elements | clang++  | g++ 
|-------------------------------:|-----:|-----:|
| `std::vector<u64>`, using `auto&` | 2.35 µs | 2.34 µs|
| `std::vector<u64>`, using iterator | 0.9956x | 0.9821x|
| `std::list<u64>`, using `auto&` | 3.9111x | 3.9286x|
| `std::list<u64>`, using iterator | 3.9111x | 3.9286x|
| `std::deque<u64>`, using `auto&` | 1.0667x | 1.0714x|
| `std::deque<u64>`, using iterator | 1.0667x | 2.0759x|
| `std::set<u64>`, using `auto&` | 21.9022x | 23.2143x|
| `std::set<u64>`, using iterator | 21.9022x | 24.0000x|
| `std::unordered_set<u64>`, using `auto&` | 3.9111x | 4.0178x|
| `std::unordered_set<u64>`, using iterator | 3.9111x | 4.0178x|
| `std::map<u64, u64>`, using `auto&` | 24.2963x | 26.7857x|
| `std::map<u64, u64>`, using iterator | 23.7037x | 26.1905x|
| `std::unordered_map<u64, u64>`, using `auto&` | 4.8593x | 3.9583x|
| `std::unordered_map<u64, u64>`, using iterator | 4.9778x | 4.0178x|

<br/><br/>

| iterating over 100'000 elements | clang++  | g++ 
|--------------------------------:|-----:|-----:|
| `std::vector<u64>`, using `auto&` | 23.54 µs | 23.02 µs|
| `std::vector<u64>`, using iterator | 1.0000x | 1.0000x|
| `std::list<u64>`, using `auto&` | 4.1776x | 4.1817x|
| `std::list<u64>`, using iterator | 4.2665x | 4.2726x|
| `std::deque<u64>`, using `auto&` | 1.0578x | 1.0909x|
| `std::deque<u64>`, using iterator | 1.0667x | 2.1364x|
| `std::set<u64>`, using `auto&` | 27.8522x | 28.7882x|
| `std::set<u64>`, using iterator | 27.8522x | 29.5458x|
| `std::unordered_set<u64>`, using `auto&` | 4.1482x | 4.2726x|
| `std::unordered_set<u64>`, using iterator | 4.1776x | 4.3635x|
| `std::map<u64, u64>`, using `auto&` | 29.6300x | 30.3034x|
| `std::map<u64, u64>`, using iterator | 28.8892x | 30.3034x|
| `std::unordered_map<u64, u64>`, using `auto&` | 5.0964x | 4.2425x|
| `std::unordered_map<u64, u64>`, using iterator | 4.9778x | 4.1817x|

<br/><br/>

| iterating over 1'000'000 elements | clang++  | g++ 
|----------------------------------:|-----:|-----:|
| `std::vector<u64>`, using `auto&` | 230.16 µs | 230.16 µs|
| `std::vector<u64>`, using iterator | 1.0227x | 1.0000x|
| `std::list<u64>`, using `auto&` | 12.3430x | 11.9960x|
| `std::list<u64>`, using iterator | 12.0858x | 12.0858x|
| `std::deque<u64>`, using `auto&` | 1.0910x | 1.0668x|
| `std::deque<u64>`, using iterator | 1.0910x | 2.1214x|
| `std::set<u64>`, using `auto&` | 61.8520x | 63.8132x|
| `std::set<u64>`, using iterator | 63.8132x | 63.3606x|
| `std::unordered_set<u64>`, using `auto&` | 12.0858x | 11.0572x|
| `std::unordered_set<u64>`, using iterator | 11.9960x | 11.5715x|
| `std::map<u64, u64>`, using `auto&` | 70.9035x | 78.8950x|
| `std::map<u64, u64>`, using iterator | 70.9035x | 78.8950x|
| `std::unordered_map<u64, u64>`, using `auto&` | 11.3144x | 11.8287x|
| `std::unordered_map<u64, u64>`, using iterator | 11.3144x | 11.8287x|

<br/><br/>

</details>
<details><summary>--- <b>Only Keeping Unique Elements</b> ---</summary>

<br/>

A typical situation is filtering a list of elements, only keeping unique ones.<br/>
While a `std::set` or `std::unordered_set` does just that, it may be preferable to use a `std::vector` instead and delete duplicates in the end.<br/>
<br/>
This benchmark explores the differences in various approaches to solve said task, for several levels of collision.<br/>
p% collision means that out of the inserted values p% of the values appear more than once and thus have to be filtered out.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| inserting 10'000 elements, 0% collision | clang++  | g++ 
|----------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 369.70 µs | 401.09 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0955x | 0.9044x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3208x | 1.3913x|
| using `std::set<u64>`, elements added all at once | 2.6026x | 2.8000x|
| using `std::set<u64>`, elements added one-by-one | 2.9057x | 2.7391x|
| using `std::unordered_set<u64>`, elements added all at once | 1.3208x | 1.3217x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.8491x | 1.7043x|

<br/><br/>

| inserting 10'000 elements, 25% collision | clang++  | g++ 
|-----------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 418.53 µs | 435.29 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 0.9752x | 0.9758x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3176x | 1.0897x|
| using `std::set<u64>`, elements added all at once | 2.0833x | 2.1313x|
| using `std::set<u64>`, elements added one-by-one | 2.3490x | 2.2585x|
| using `std::unordered_set<u64>`, elements added all at once | 1.0500x | 1.0208x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.7083x | 1.4422x|

<br/><br/>

| inserting 10'000 elements, 50% collision | clang++  | g++ 
|-----------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 404.53 µs | 427.25 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0562x | 1.0630x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3133x | 1.1755x|
| using `std::set<u64>`, elements added all at once | 1.5950x | 1.6156x|
| using `std::set<u64>`, elements added one-by-one | 1.7933x | 1.8612x|
| using `std::unordered_set<u64>`, elements added all at once | 0.8277x | 0.8824x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.2677x | 1.1703x|

<br/><br/>

| inserting 10'000 elements, 75% collision | clang++  | g++ 
|-----------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 404.99 µs | 371.09 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0524x | 1.0573x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.2015x | 1.1485x|
| using `std::set<u64>`, elements added all at once | 1.2732x | 1.6917x|
| using `std::set<u64>`, elements added one-by-one | 1.2346x | 1.8797x|
| using `std::unordered_set<u64>`, elements added all at once | 0.6511x | 0.5865x|
| using `std::unordered_set<u64>`, elements added one-by-one | 0.8906x | 0.9472x|

<br/><br/>

| inserting 10'000 elements, 100% collision | clang++  | g++ 
|------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 59.38 µs | 60.94 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 0.9868x | 1.0073x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.0573x | 0.8700x|
| using `std::set<u64>`, elements added all at once | 0.1974x | 0.2513x|
| using `std::set<u64>`, elements added one-by-one | 0.5075x | 0.2043x|
| using `std::unordered_set<u64>`, elements added all at once | 1.5038x | 1.5453x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.6731x | 1.6250x|

<br/><br/>

| inserting 100'000 elements, 0% collision | clang++  | g++ 
|-----------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 4.74 ms | 4.53 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 0.9545x | 0.9848x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3182x | 1.4132x|
| using `std::set<u64>`, elements added all at once | 3.5884x | 4.0353x|
| using `std::set<u64>`, elements added one-by-one | 3.3687x | 4.0058x|
| using `std::unordered_set<u64>`, elements added all at once | 1.4170x | 1.3233x|
| using `std::unordered_set<u64>`, elements added one-by-one | 2.0597x | 1.8850x|

<br/><br/>

| inserting 100'000 elements, 25% collision | clang++  | g++ 
|------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 4.63 ms | 4.80 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0791x | 1.1202x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3549x | 1.3671x|
| using `std::set<u64>`, elements added all at once | 3.3721x | 3.5725x|
| using `std::set<u64>`, elements added one-by-one | 3.3721x | 3.6518x|
| using `std::unordered_set<u64>`, elements added all at once | 1.1742x | 1.0416x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.6860x | 1.5624x|

<br/><br/>

| inserting 100'000 elements, 50% collision | clang++  | g++ 
|------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 4.82 ms | 4.60 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.1013x | 1.0909x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3014x | 1.5152x|
| using `std::set<u64>`, elements added all at once | 2.5450x | 3.3939x|
| using `std::set<u64>`, elements added one-by-one | 2.5049x | 3.3939x|
| using `std::unordered_set<u64>`, elements added all at once | 0.8219x | 0.8702x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.2309x | 1.3030x|

<br/><br/>

| inserting 100'000 elements, 75% collision | clang++  | g++ 
|------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 4.72 ms | 4.87 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0927x | 0.8851x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.0643x | 1.1550x|
| using `std::set<u64>`, elements added all at once | 1.8101x | 2.3956x|
| using `std::set<u64>`, elements added one-by-one | 1.8984x | 2.5065x|
| using `std::unordered_set<u64>`, elements added all at once | 0.5869x | 0.4612x|
| using `std::unordered_set<u64>`, elements added one-by-one | 0.7791x | 0.8021x|

<br/><br/>

| inserting 100'000 elements, 100% collision | clang++  | g++ 
|-------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 578.12 µs | 704.02 µs|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.1622x | 1.2181x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.0811x | 0.9165x|
| using `std::set<u64>`, elements added all at once | 0.2389x | 0.1833x|
| using `std::set<u64>`, elements added one-by-one | 0.4157x | 0.1739x|
| using `std::unordered_set<u64>`, elements added all at once | 1.4834x | 1.2633x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.6870x | 1.4261x|

<br/><br/>

| inserting 1'000'000 elements, 0% collision | clang++  | g++ 
|-------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 56.25 ms | 57.81 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0000x | 1.0074x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.3384x | 1.2913x|
| using `std::set<u64>`, elements added all at once | 10.1389x | 11.0811x|
| using `std::set<u64>`, elements added one-by-one | 10.2778x | 10.8108x|
| using `std::unordered_set<u64>`, elements added all at once | 2.5556x | 2.4865x|
| using `std::unordered_set<u64>`, elements added one-by-one | 4.1667x | 4.0541x|

<br/><br/>

| inserting 1'000'000 elements, 25% collision | clang++  | g++ 
|--------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 56.82 ms | 59.66 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0250x | 0.9524x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.2833x | 1.1931x|
| using `std::set<u64>`, elements added all at once | 8.1125x | 8.7738x|
| using `std::set<u64>`, elements added one-by-one | 8.2500x | 8.6429x|
| using `std::unordered_set<u64>`, elements added all at once | 1.8071x | 1.8707x|
| using `std::unordered_set<u64>`, elements added one-by-one | 3.3000x | 3.1429x|

<br/><br/>

| inserting 1'000'000 elements, 50% collision | clang++  | g++ 
|--------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 56.25 ms | 58.24 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0354x | 1.0732x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.2626x | 1.2439x|
| using `std::set<u64>`, elements added all at once | 5.2778x | 6.1707x|
| using `std::set<u64>`, elements added one-by-one | 5.4167x | 6.1707x|
| using `std::unordered_set<u64>`, elements added all at once | 1.0043x | 1.0525x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.4683x | 1.3415x|

<br/><br/>

| inserting 1'000'000 elements, 75% collision | clang++  | g++ 
|--------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 53.98 ms | 58.24 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.0263x | 0.9659x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.1842x | 1.1220x|
| using `std::set<u64>`, elements added all at once | 2.8947x | 3.4878x|
| using `std::set<u64>`, elements added one-by-one | 2.8947x | 3.4878x|
| using `std::unordered_set<u64>`, elements added all at once | 0.5548x | 0.5263x|
| using `std::unordered_set<u64>`, elements added one-by-one | 0.7833x | 0.7333x|

<br/><br/>

| inserting 1'000'000 elements, 100% collision | clang++  | g++ 
|---------------------------------------------:|-----:|-----:|
| using `std::vector<u64>`, elements added all at once | 7.25 ms | 7.64 ms|
| using `std::vector<u64>`, elements added one-by-one, filtered in the end | 1.1200x | 1.0909x|
| using `std::vector<u64>`, elements added one-by-one, filtered halfway and in the end | 1.0051x | 0.9545x|
| using `std::set<u64>`, elements added all at once | 0.1557x | 0.1790x|
| using `std::set<u64>`, elements added one-by-one | 0.3719x | 0.1621x|
| using `std::unordered_set<u64>`, elements added all at once | 1.0769x | 1.1182x|
| using `std::unordered_set<u64>`, elements added one-by-one | 1.3462x | 1.3091x|

<br/><br/>

</details>
<details><summary>--- <b>Searching Containers</b> ---</summary>

<br/>

This benchmark explores the differences in searching objects in containers.<br/>
All tests are performed with objects that exist as well as non-existing objects.<br/>
For sortable collections, both unsorted search and sorted binary search are included.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| 10'000 elements, searching random existing element | clang++  | g++ 
|---------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 1.76 µs | 1.50 µs|
| `std::vector<u64>` (sorted, binary search) | 0.3627x | 0.4376x|
| `std::list<u64>` (unsorted) | 3.1548x | 3.7209x|
| `std::list<u64>` (sorted, binary search) | 5.4762x | 6.5581x|
| `std::deque<u64>` (unsorted) | 1.4286x | 0.9674x|
| `std::deque<u64>` (sorted, binary search) | 0.3571x | 0.4376x|
| `std::set<u64>` | 0.3472x | 0.3855x|
| `std::unordered_set<u64>` | 0.3016x | 0.3647x|
| `std::map<u64, u64>` | 0.2933x | 0.4167x|
| `std::unordered_map<u64, u64>` | 0.3095x | 0.3974x|

<br/><br/>

| 10'000 elements, searching random non-existing element | clang++  | g++ 
|-------------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 2.62 µs | 2.11 µs|
| `std::vector<u64>` (sorted, binary search) | 0.2181x | 0.2645x|
| `std::list<u64>` (unsorted) | 3.7500x | 4.8595x|
| `std::list<u64>` (sorted, binary search) | 3.6303x | 4.7603x|
| `std::deque<u64>` (unsorted) | 1.5293x | 1.5388x|
| `std::deque<u64>` (sorted, binary search) | 0.2082x | 0.3174x|
| `std::set<u64>` | 0.2502x | 0.2444x|
| `std::unordered_set<u64>` | 0.1906x | 0.2656x|
| `std::map<u64, u64>` | 0.2021x | 0.2851x|
| `std::unordered_map<u64, u64>` | 0.1906x | 0.2512x|

<br/><br/>

| 100'000 elements, searching random existing element | clang++  | g++ 
|----------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 12.28 µs | 9.21 µs|
| `std::vector<u64>` (sorted, binary search) | 0.0375x | 0.0679x|
| `std::list<u64>` (unsorted) | 4.2000x | 5.6000x|
| `std::list<u64>` (sorted, binary search) | 7.6701x | 10.9086x|
| `std::deque<u64>` (unsorted) | 1.5880x | 1.5152x|
| `std::deque<u64>` (sorted, binary search) | 0.0522x | 0.0663x|
| `std::set<u64>` | 0.0489x | 0.0696x|
| `std::unordered_set<u64>` | 0.0386x | 0.0515x|
| `std::map<u64, u64>` | 0.0573x | 0.0754x|
| `std::unordered_map<u64, u64>` | 0.0471x | 0.0591x|

<br/><br/>

| 100'000 elements, searching random non-existing element | clang++  | g++ 
|--------------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 18.42 µs | 16.04 µs|
| `std::vector<u64>` (sorted, binary search) | 0.0322x | 0.0429x|
| `std::list<u64>` (unsorted) | 5.1704x | 6.1302x|
| `std::list<u64>` (sorted, binary search) | 5.1134x | 6.2391x|
| `std::deque<u64>` (unsorted) | 2.0833x | 1.7370x|
| `std::deque<u64>` (sorted, binary search) | 0.0318x | 0.0426x|
| `std::set<u64>` | 0.0341x | 0.0390x|
| `std::unordered_set<u64>` | 0.0314x | 0.0351x|
| `std::map<u64, u64>` | 0.0339x | 0.0470x|
| `std::unordered_map<u64, u64>` | 0.0288x | 0.0391x|

<br/><br/>

| 1'000'000 elements, searching random existing element | clang++  | g++ 
|------------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 119.63 µs | 83.71 µs|
| `std::vector<u64>` (sorted, binary search) | 0.0060x | 0.0078x|
| `std::list<u64>` (unsorted) | 9.7959x | 13.7083x|
| `std::list<u64>` (sorted, binary search) | 11.3703x | 22.4734x|
| `std::deque<u64>` (unsorted) | 1.5395x | 1.6499x|
| `std::deque<u64>` (sorted, binary search) | 0.0061x | 0.0086x|
| `std::set<u64>` | 0.0066x | 0.0108x|
| `std::unordered_set<u64>` | 0.0054x | 0.0084x|
| `std::map<u64, u64>` | 0.0075x | 0.0097x|
| `std::unordered_map<u64, u64>` | 0.0065x | 0.0071x|

<br/><br/>

| 1'000'000 elements, searching random non-existing element | clang++  | g++ 
|----------------------------------------------------------:|-----:|-----:|
| `std::vector<u64>` (unsorted) | 180.30 µs | 184.17 µs|
| `std::vector<u64>` (sorted, binary search) | 0.0035x | 0.0037x|
| `std::list<u64>` (unsorted) | 14.7715x | 14.4615x|
| `std::list<u64>` (sorted, binary search) | 7.4827x | 9.7974x|
| `std::deque<u64>` (unsorted) | 2.0423x | 1.4657x|
| `std::deque<u64>` (sorted, binary search) | 0.0042x | 0.0037x|
| `std::set<u64>` | 0.0041x | 0.0042x|
| `std::unordered_set<u64>` | 0.0029x | 0.0036x|
| `std::map<u64, u64>` | 0.0048x | 0.0044x|
| `std::unordered_map<u64, u64>` | 0.0033x | 0.0043x|

<br/><br/>

</details>
<details><summary>--- <b>Std Function Vs Function Ptr</b> ---</summary>

<br/>

This benchmark explores the call overhead of invoking a list of `std::function` compared to function pointers, both stored in a `std::vector`.<br/>
Content of the functions is similar.<br/>
A typical situation where this is interesting would be invoking (a collection of) callback functions.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| 10'000 function calls | clang++  | g++ 
|----------------------:|-----:|-----:|
| via function pointer | 87.89 µs | 153.46 µs|
| via `std::function` | 1.2223x | 1.0999x|

<br/><br/>

| 100'000 function calls | clang++  | g++ 
|-----------------------:|-----:|-----:|
| via function pointer | 889.37 µs | 1.53 ms|
| via `std::function` | 1.2078x | 1.1007x|

<br/><br/>

| 1'000'000 function calls | clang++  | g++ 
|-------------------------:|-----:|-----:|
| via function pointer | 8.75 ms | 15.28 ms|
| via `std::function` | 1.2556x | 1.0976x|

<br/><br/>

</details>
<details><summary>--- <b>Using Objects Vs Object Pointers</b> ---</summary>

<br/>

This benchmark explores the difference in accessing "large" structs either directly or through smart/raw pointers to such objects.<br/>
<br/>

Baseline results (first line) report absolute CPU time.<br/>
All other results report relative increase to the baseline (<1.0 means faster, >1.0 means slower).<br/>
<br/><br/>

| accessing 10'000 objects (128 bytes each) | clang++  | g++ 
|------------------------------------------:|-----:|-----:|
| access stack-allocated contiguous objects | 7.50 µs | 2.35 µs|
| access via raw pointers to heap-allocated objects | 1.1163x | 1.0000x|
| access via unique pointers | 1.1163x | 0.9778x|
| access via shared pointers | 1.1721x | 1.0000x|

<br/><br/>

| accessing 100'000 objects (128 bytes each) | clang++  | g++ 
|-------------------------------------------:|-----:|-----:|
| access stack-allocated contiguous objects | 76.73 µs | 23.02 µs|
| access via raw pointers to heap-allocated objects | 1.1181x | 1.0000x|
| access via unique pointers | 1.0909x | 1.0227x|
| access via shared pointers | 1.2545x | 1.0227x|

<br/><br/>

| accessing 1'000'000 objects (128 bytes each) | clang++  | g++ 
|---------------------------------------------:|-----:|-----:|
| access stack-allocated contiguous objects | 3.61 ms | 235.40 µs|
| access via raw pointers to heap-allocated objects | 1.1337x | 1.0000x|
| access via unique pointers | 1.1378x | 1.0000x|
| access via shared pointers | 1.1917x | 1.2668x|

<br/><br/>

| reordering 10'000 objects (128 bytes each) | clang++  | g++ 
|-------------------------------------------:|-----:|-----:|
| shuffling objects | 2.34 ms | 2.40 ms|
| shuffling raw pointers | 0.9588x | 0.9547x|

<br/><br/>

| reordering 100'000 objects (128 bytes each) | clang++  | g++ 
|--------------------------------------------:|-----:|-----:|
| shuffling objects | 46.88 ms | 46.88 ms|
| shuffling raw pointers | 0.9556x | 0.9556x|

<br/><br/>

| reordering 1'000'000 objects (128 bytes each) | clang++  | g++ 
|----------------------------------------------:|-----:|-----:|
| shuffling objects | 531.25 ms | 531.25 ms|
| shuffling raw pointers | 0.8676x | 0.8676x|

<br/><br/>

</details>
