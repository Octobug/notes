const LANG = {
  ARABIC: 'Arabic',
  BENGALI: 'Bengali',
  BULGARIAN: 'Bulgarian',
  CHINESE: 'Chinese',
  CZECH: 'Czech',
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
  HUNGARIAN: 'Hungarian',
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
  SERBIAN: 'Serbian',
  SLOVAK: 'Slovak',
  SPANISH: 'Spanish',
  SWEDISH: 'Swedish',
  TAGALOG: 'Tagalog',
  TAMIL: 'Tamil',
  THAI: 'Thai',
  TURKISH: 'Turkish',
  UKRAINIAN: 'Ukrainian',
  VIETNAMESE: 'Vietnamese',
};

const NORMALIZATION = 10;
const scores = {};

function updateScore(lang, score) {
  if (scores[lang]) {
    scores[lang] += score;
  } else {
    scores[lang] = score;
  }
}

function reversalScore(langs, weight = 1) {
  langs.slice().reverse().forEach((lang, index) => {
    const score = (index + 1) * NORMALIZATION / langs.length;
    updateScore(lang, score * weight);
  });
}

function rankByLangGDP() {
  // https://www.reddit.com/r/languagelearning/comments/11xt73g/world_languages_by_gdp_2023_edition/
  const langs = [
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

  reversalScore(langs, 3);
}

function rankByNationGDP() {
  // https://en.wikipedia.org/wiki/List_of_countries_by_GDP_(nominal)
  const langs = [
    // 01-10
    LANG.ENGLISH, // United States
    LANG.CHINESE, // PRC
    LANG.GERMAN, // Germany
    LANG.JAPANESE, // Japan
    [LANG.HINDI, LANG.ENGLISH], // India
    LANG.ENGLISH, // United Kingdom
    LANG.FRENCH, // France
    LANG.ITALIAN, // Italy
    LANG.PORTUGUESE, // Brazil
    [LANG.ENGLISH, LANG.FRENCH], // Canada
    // 11-20
    LANG.RUSSIAN, // Russia
    LANG.SPANISH, // Mexico
    LANG.KOREAN, // South Korea
    LANG.ENGLISH, // Australia
    LANG.SPANISH, // Spain
    LANG.MALAY_INDONESIAN, // Indonesia
    LANG.TURKISH, // Turkey
    LANG.DUTCH, // Netherlands
    LANG.ARABIC, // Saudi Arabia
    [LANG.GERMAN, LANG.FRENCH, LANG.ITALIAN, LANG.ROMANSH], // Switzerland
    // 21-30
    LANG.POLISH, // Poland
    LANG.CHINESE, // ROC
    [LANG.DUTCH, LANG.FRENCH, LANG.GERMAN], // Belgium
    LANG.SPANISH, // Argentina
    LANG.SWEDISH, // Sweden
    [LANG.IRISH, LANG.ENGLISH], // Ireland
    [LANG.NORWEGIAN, LANG.SAMI], // Norway
    LANG.GERMAN, // Austria
    LANG.HEBREW, // Israel
    LANG.THAI, // Thailand
    // 31-
    LANG.ARABIC, // United Arab Emirates
    [LANG.ENGLISH, LANG.MALAY_INDONESIAN, LANG.CHINESE, LANG.TAMIL], // Singapore
  ];

  langs.slice().reverse().forEach((langItems, index) => {
    if (!(langItems instanceof Array)) {
      langItems = [langItems];
    }

    const score = (index + 1) * NORMALIZATION / langs.length;
    const weight = 2;
    for (const lang of langItems) {
      updateScore(lang, score / langItems.length * weight);
    }
  });
}

function rankByDuolingoTop10() {
  // https://blog.duolingo.com/2023-duolingo-language-report/
  const langs = [
    LANG.ENGLISH,
    LANG.SPANISH,
    LANG.FRENCH,
    LANG.GERMAN,
    LANG.JAPANESE,
    LANG.KOREAN,
    LANG.ITALIAN,
    LANG.HINDI,
    LANG.CHINESE,
    LANG.PORTUGUESE,
  ];

  reversalScore(langs);
}

function rankByInternetLanguages() {
  // https://en.wikipedia.org/wiki/Languages_used_on_the_Internet
  const langs = [
    // 01-10
    LANG.ENGLISH,
    LANG.SPANISH,
    LANG.GERMAN,
    LANG.RUSSIAN,
    LANG.JAPANESE,
    LANG.FRENCH,
    LANG.PORTUGUESE,
    LANG.ITALIAN,
    LANG.TURKISH,
    LANG.DUTCH,
    // 11-20
    LANG.POLISH,
    LANG.PERSIAN,
    LANG.CHINESE,
    LANG.VIETNAMESE,
    LANG.MALAY_INDONESIAN,
    LANG.CZECH,
    LANG.KOREAN,
    LANG.ARABIC,
    LANG.UKRAINIAN,
    LANG.GREEK,
    // 21-30
    LANG.HEBREW,
    LANG.SWEDISH,
    LANG.ROMANIAN,
    LANG.THAI,
    LANG.DANISH,
    LANG.SLOVAK,
    LANG.FINNISH,
    LANG.BULGARIAN,
    LANG.SERBIAN,
  ];

  reversalScore(langs);
}

function main() {
  rankByLangGDP();
  rankByNationGDP();
  rankByDuolingoTop10();
  rankByInternetLanguages();

  const sorted = Object.entries(scores).sort((a, b) => {
    const [, scoreA] = a;
    const [, scoreB] = b;
    return scoreB - scoreA;
  });

  const coefficient100 = 100 / sorted[0][1];

  sorted.forEach(([lang, score], index) => {
    console.log(
      `${index + 1}. ${lang}: ${(score * coefficient100).toFixed(2)}`
    );
  });
}

main();
