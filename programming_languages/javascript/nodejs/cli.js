const yargs = require('yargs');

const main = async () => {
  const validTypes = [
    'all',
  ];
  const DEFAULT = 'all';
  const argv = yargs
    .option('type', {
      alias: 't',
      description: `Specify the data type,
        availables: [${validTypes.join(', ')}]
        default: ${DEFAULT}`,
      type: 'string',
    })
    .usage('Usage: $0 [-t <type>] arg ...')
    .help()
    .alias('help', 'h')
    .argv;

  if (argv._.length) {
    const type = argv.t || DEFAULT;
    if (!validTypes.includes(type)) {
      throw new Error(`invalid type: ${type}`);
    }

    return;
  }
  yargs.showHelp();
};

main().catch(err => {
  console.log(err);
});
