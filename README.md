# AYKVMSBB

Command-line tool for retrieving currency exchange rates

## Preamble

One day I was so freaking bored that decided to chill out on one of the most famous local forums called "linux.org.ru". I saw there incredibly exciting stuff: some crazy (in good sense) fellows showed their programs with weird long acronym-like names. One of these guys parodied the other one, so I decided to join that "squishy troll" party...

## What is it?

This program is created to retreive currencies from online sources. The common features are:

1. No external dependecies. Program requires only any POSIX compatiable system to run and c99 compatiable compiler to build.
2. You can specify (or not specify!) currency and date in any sequence.
3. Possibility to omit year or year&month when specifying the date.
4. Specifying day from future returns results from previous month.
5. Uses XML api.
6. If XML api supports currency nominal (amount of currency for value), displays is among with currency value.
7. Fast engineless embedded database.

## Usage

Step 1. Retrieve and build program program:
```
git clone https://github.com/xdevelnet/AYKVMSBB.git
cd AYKVMSBB
make
```
Step 2. Use it:
```
./aykvmsbb
USD: 26.070702
```
Step 3. You may also wish to install it - just copy aykvmsbb binary to any ENV dir.

## More

Q: Is it really useful?

A: I would rather say that it is "handy" rather than "useful". Typing "ay" and pressing "TAB" will complete program name, then you can press ENTER button immediatly, or add currency as argument, needed date, or both.

Q: So, what exactly AYKVMSBB means?

A: AYKVMSBB stands for "ALLO YOBA KURS VALYT MNE SYDA BISTRO BLYAT" which is transliterated russian phrase. Rough translation: 
"Hey, Yoba, give me exchange rates here, faster, bitch".

Q: How to add my country/bank?

A: Check out contents of rodata.h and fill in new records to database.

Q: Pull request?

A: Always welcome! <3

Q: I found a huge piece of garbage in your code.

A: Just as planned. Now we can discuss about that if you want. Btw, shitty things inside this project is nothing unusual. Just relax and have fun!

Q: List of supported countries/banks please?

A:

1. Russia: Central Bank of the Russian Federation
2. Ukraine: National Bank of Ukraine
