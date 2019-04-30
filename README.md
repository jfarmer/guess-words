# Guess Words

This is a 15-year-old old college project of mine from [John Goldsmith's](john-goldsmith) introductory computational linguistics course.

It uses statistical techniques to produce the most likely sequence of words from a stream of unbroken characters.

The statistical model of word boundaries is a naïve unigram model create from training data.  It uses the [Viterbi algorithm](wiki-viterbi) to generate the most likely sequence of words given the unbroken string of characters.

## NOTE!!!

I haven't touched this code in 15 years. I'm posting it to illustrate the use of dynamic programming in practice. I realize:

- There are many problems with the statistical model
- The quality of the C++ is questionable

I was a self-taught, 20-year-old programmer when I wrote this. Be happy I gave logically organized code, a `Makefile`, command line options, and a useful help message!

## Installing

To compile, make sure you have a working instance of `g++` and run

```console
$ make
```

Run

```console
$ ./viterbi -h
```

to see a help message.

Run this to parse the words out of a particular sentence:

```console
$ ./viterbi -s 'whenwilltheygethere'
```

You can run `./viterbi -s -` to tell it to read from STDIN.

## Output

The output is noisy:

```console
$ ./viterbi -s 'whenwilltheygethere'
Loading lexicon from "data/kjv"...done
Computing character statistics...done
	Word count:	3254640
	Singleton plog:	21.6341 bits
Computing word statistics...done
	Lexicon size:	18865
	Max. length:	19
Parsing string "whenwilltheygethere"...done
-when-will-they-get-here
$
```

Internally, the probabilities are stored as [log probabilities](wiki-log-probability), which is a common technique to handle small probabilities.  If your probabilities are very small and you use them normally, then the product of many small probabilities is likely to end up being `0` as a float/double.

The "singleton plog" is the log probability of a word we haven't seen in our training corpus. It is `log(1 / wordsInTrainingCorpus)`, i.e., we act "as if" we've seen any word once.

This creates issues because the unknown word `"q"` is just as likely as the unknown word `"hellish"`.  Our model is too naïve to say the latter is more likely than the former.  Want to submit a pull request? ;)

## Training Data

By default it uses the KJV to generate words.  This makes for an ...interesting... vocabulary. For example, the likelihood of "hell" being a word is very, very high.

See [data/kjv](data/kjv).  You can supply your own training corpus with the `-d` option.

[john-goldsmith]: http://people.cs.uchicago.edu/~jagoldsm/
[wiki-viterbi]: https://en.wikipedia.org/wiki/Viterbi_algorithm
[wiki-log-probability]: https://en.wikipedia.org/wiki/Log_probability
