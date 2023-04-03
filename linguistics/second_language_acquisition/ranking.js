const LANG = {
  ARABIC: 'Arabic',
  BENGALI: 'Bengali',
  CHINESE: 'Chinese',
  DUTCH: 'Dutch',
  ENGLISH: 'English',
  FRENCH: 'French',
  GERMAN: 'German',
  HINDI: 'Hindi',
  ITALIAN: 'Italian',
  JAPANESE: 'Japanese',
  KOREAN: 'Korean',
  MALAY_INDONESIAN: 'Malay-Indonesian',
  PERSIAN: 'Persian',
  POLISH: 'Polish',
  PORTUGUESE: 'Portuguese',
  PUNJABI: 'Punjabi',
  RUSSIAN: 'Russian',
  SPANISH: 'Spanish',
  THAI: 'Thai',
  TURKISH: 'Turkish',
  VIETNAMESE: 'Vietnamese',
};

const rankByLangGDP = [
  LANG.ENGLISH,
  LANG.CHINESE,
  LANG.SPANISH,
  LANG.GERMAN,
  LANG.ARABIC,
  LANG.JAPANESE,
  LANG.RUSSIAN,
  LANG.MALAY_INDONESIAN,
  LANG.PORTUGUESE,
  LANG.FRENCH,
  LANG.TURKISH,
  LANG.ITALIAN,
  LANG.KOREAN,
  LANG.DUTCH,
  LANG.POLISH,
  LANG.THAI,
  LANG.PERSIAN,
  LANG.VIETNAMESE,
  LANG.PUNJABI,
  LANG.BENGALI
];

const rankByNationGDP = [
  LANG.ENGLISH,
  LANG.CHINESE,
  LANG.JAPANESE,
  LANG.GERMAN,
  LANG.HINDI,
  LANG.ENGLISH,
  LANG.FRENCH,
  LANG.ENGLISH,
  LANG.RUSSIAN,
  LANG.ITALIAN,
  LANG.PERSIAN,
  LANG.PORTUGUESE,
  LANG.KOREAN,
  LANG.ENGLISH,
  LANG.SPANISH,
  LANG.SPANISH,
  LANG.MALAY_INDONESIAN,
  LANG.ARABIC,
  LANG.DUTCH,
  LANG.TURKISH
];

const scores = {};

rankByLangGDP.slice(0).reverse().forEach((lang, index) => {
  const score = index + 1;
  scores[lang] = score;
});

rankByNationGDP.slice(0).reverse().forEach((lang, index) => {
  const score = index + 1;
  if (scores[lang]) {
    scores[lang] += score;
  } else {
    scores[lang] = score;
  }
});

Object.entries(scores).sort((a, b) => {
  const [, scoreA] = a;
  const [, scoreB] = b;
  return scoreB - scoreA;
}).forEach(([lang, score],) => {
  console.log(`${lang}: ${score}`);
});
