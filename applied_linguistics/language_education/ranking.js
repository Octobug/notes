const LANG = {
  ARABIC: 'Arabic',
  BENGALI: 'Bengali',
  BULGARIAN: 'Bulgarian',
  CHINESE: 'Chinese',
  CROATIAN: 'Croatian',
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
    LANG.ENGLISH, // United Kingdom
    [LANG.HINDI, LANG.ENGLISH], // India
    LANG.FRENCH, // France
    LANG.ITALIAN, // Italy
    LANG.RUSSIAN, // Russia
    LANG.PORTUGUESE, // Brazil
    // 11-20
    [LANG.ENGLISH, LANG.FRENCH], // Canada
    LANG.ENGLISH, // Australia
    LANG.SPANISH, // Mexico
    LANG.SPANISH, // Spain
    LANG.KOREAN, // South Korea
    LANG.TURKISH, // Turkey
    LANG.MALAY_INDONESIAN, // Indonesia
    LANG.DUTCH, // Netherlands
    LANG.ARABIC, // Saudi Arabia
    [LANG.GERMAN, LANG.FRENCH, LANG.ITALIAN, LANG.ROMANSH], // Switzerland
    // 21-30
    LANG.POLISH, // Poland
    LANG.CHINESE, // ROC
    [LANG.IRISH, LANG.ENGLISH], // Ireland
    [LANG.DUTCH, LANG.FRENCH, LANG.GERMAN], // Belgium
    LANG.SWEDISH, // Sweden
    LANG.HEBREW, // Israel
    LANG.SPANISH, // Argentina
    [LANG.ENGLISH, LANG.MALAY_INDONESIAN, LANG.CHINESE, LANG.TAMIL], // Singapore
    LANG.GERMAN, // Austria
    LANG.ARABIC, // United Arab Emirates
    // 31-
    [LANG.NORWEGIAN, LANG.SAMI], // Norway
    LANG.THAI, // Thailand
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
  // https://blog.duolingo.com/2025-duolingo-language-report/
  const langs = [
    LANG.ENGLISH,
    LANG.SPANISH,
    LANG.FRENCH,
    LANG.JAPANESE,
    LANG.GERMAN,
    LANG.KOREAN,
    LANG.ITALIAN,
    LANG.CHINESE,
    LANG.PORTUGUESE,
    LANG.HINDI,
  ];

  reversalScore(langs, 2);
}

function rankByInternetLanguages() {
  // https://en.wikipedia.org/wiki/Languages_used_on_the_Internet
  const langs = [
    // 01-10
    LANG.ENGLISH,
    LANG.SPANISH,
    LANG.GERMAN,
    LANG.JAPANESE,
    LANG.FRENCH,
    LANG.PORTUGUESE,
    LANG.RUSSIAN,
    LANG.ITALIAN,
    LANG.DUTCH,
    LANG.POLISH,
    // 11-20
    LANG.TURKISH,
    LANG.CHINESE,
    LANG.PERSIAN,
    LANG.VIETNAMESE,
    LANG.CZECH,
    LANG.MALAY_INDONESIAN,
    LANG.KOREAN,
    LANG.UKRAINIAN,
    LANG.ARABIC,
    LANG.HUNGARIAN,
    // 21-30
    LANG.SWEDISH,
    LANG.ROMANIAN,
    LANG.GREEK,
    LANG.DANISH,
    LANG.FINNISH,
    LANG.HEBREW,
    LANG.SLOVAK,
    LANG.THAI,
    LANG.BULGARIAN,
    LANG.CROATIAN,
  ];

  reversalScore(langs, 1);
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
