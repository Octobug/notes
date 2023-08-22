const LANG = {
  ARABIC: 'Arabic',
  BENGALI: 'Bengali',
  CHINESE: 'Chinese',
  DANISH: 'Danish',
  DUTCH: 'Dutch',
  ENGLISH: 'English',
  FARSI: 'Farsi',
  FINNISH: 'Finnish',
  FRENCH: 'French',
  GERMAN: 'German',
  GREEK: 'Greek',
  HEBREW: 'Hebrew',
  HINDI: 'Hindi',
  IRISH: 'Irish',
  ITALIAN: 'Italian',
  JAPANESE: 'Japanese',
  JAVANESE: 'Javanese',
  KOREAN: 'Korean',
  MALAY_INDONESIAN: 'Malay-Indonesian',
  NORWEGIAN: 'Norwegian',
  PERSIAN: 'Persian',
  POLISH: 'Polish',
  PORTUGUESE: 'Portuguese',
  PUNJABI: 'Punjabi',
  ROMANIAN: 'Romanian',
  ROMANSH: 'Romansh',
  RUSSIAN: 'Russian',
  SAMI: 'Sami',
  SPANISH: 'Spanish',
  SWEDISH: 'Swedish',
  TAGALOG: 'Tagalog',
  TAMIL: 'Tamil',
  THAI: 'Thai',
  TURKISH: 'Turkish',
  VIETNAMESE: 'Vietnamese',
};

const rankByLangGDP = [
  // 01-10
  LANG.ENGLISH,
  LANG.CHINESE,
  LANG.SPANISH,
  LANG.JAPANESE,
  LANG.GERMAN,
  LANG.FRENCH,
  LANG.ARABIC,
  LANG.ITALIAN,
  LANG.PORTUGUESE,
  LANG.KOREAN,
  // 11-20
  LANG.RUSSIAN,
  LANG.HINDI,
  LANG.DUTCH,
  LANG.TURKISH,
  LANG.MALAY_INDONESIAN,
  LANG.BENGALI,
  LANG.POLISH,
  LANG.SWEDISH,
  LANG.THAI,
  LANG.FARSI,
  // 21-30
  LANG.VIETNAMESE,
  LANG.NORWEGIAN,
  LANG.PUNJABI,
  LANG.DANISH,
  LANG.HEBREW,
  LANG.JAVANESE,
  LANG.GREEK,
  LANG.TAGALOG,
  LANG.ROMANIAN,
  LANG.FINNISH,
];

const rankByNationGDP = [
  // 01-10
  LANG.ENGLISH,
  LANG.CHINESE,
  LANG.JAPANESE,
  LANG.GERMAN,
  [LANG.HINDI, LANG.ENGLISH],
  LANG.ENGLISH,
  LANG.FRENCH,
  LANG.ITALIAN,
  [LANG.ENGLISH, LANG.FRENCH],
  LANG.PORTUGUESE,
  // 11-20
  LANG.RUSSIAN,
  LANG.KOREAN,
  LANG.ENGLISH,
  LANG.SPANISH,
  LANG.SPANISH,
  LANG.MALAY_INDONESIAN,
  LANG.DUTCH,
  LANG.ARABIC,
  LANG.TURKISH,
  [LANG.GERMAN, LANG.FRENCH, LANG.ITALIAN, LANG.ROMANSH],
  // 21-30
  LANG.CHINESE,
  LANG.POLISH,
  LANG.SPANISH,
  [LANG.DUTCH, LANG.FRENCH, LANG.GERMAN],
  LANG.SWEDISH,
  [LANG.IRISH, LANG.ENGLISH],
  LANG.THAI,
  [LANG.NORWEGIAN, LANG.SAMI],
  LANG.HEBREW,
  [LANG.ENGLISH, LANG.MALAY_INDONESIAN, LANG.CHINESE, LANG.TAMIL],
];

const scores = {};

rankByLangGDP.slice(0).reverse().forEach((lang, index) => {
  const score = (index + 1) * 2;
  scores[lang] = score;
});

rankByNationGDP.slice(0).reverse().forEach((langs, index) => {
  if (!(langs instanceof Array)) {
    langs = [langs];
  }

  const score = (index + 1) / langs.length;
  for (const lang of langs) {
    if (scores[lang]) {
      scores[lang] += score;
    } else {
      scores[lang] = score;
    }
  }
});


const sorted = Object.entries(scores).sort((a, b) => {
  const [, scoreA] = a;
  const [, scoreB] = b;
  return scoreB - scoreA;
});

const coefficient100 = 100 / sorted[0][1];

sorted.forEach(([lang, score],) => {
  console.log(`${lang}: ${(score * coefficient100).toFixed(2)}`);
});
