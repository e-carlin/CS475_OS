#define ALPHABET_SIZE 26

typedef struct WordStats {
    int histo[ALPHABET_SIZE];
    int wordCount;
    int vowelCount;
    int consonantCount;
} WordStats;

WordStats initStats(WordStats);
WordStats updateStats(WordStats, const char[]);
WordStats incrementWordCount(WordStats);
WordStats updateVowelConsCount(WordStats, const char[]);
WordStats updateHistogramCount(WordStats, const char[]);

void printVowelConsFreq(WordStats);
void printWordCount(WordStats);
void printHistogram(WordStats);

