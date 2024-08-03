# Loggin

## winston

```ts
import winston, {
  Logform,
  Logger,
  LoggerOptions,
  format,
  transports
} from 'winston';
import * as env from './env';

export type LogItem = {
  timestamp: string,
  label: string,
  level: string,
  message: string,
  extra: unknown
};

function parseLogItem(line: Logform.TransformableInfo): LogItem {
  const { timestamp, label, level, message } = line;
  const splat: Logform.Format[] = line[Symbol.for('splat')] || [];
  if (splat.length > 1) {
    throw new Error('logger only accepts 1 extra object, '
      + `provided: ${splat.length}`);
  }
  const extra = splat[0];
  return { timestamp, label, level, message, extra };
}

function toString(message: unknown) {
  if (!message) {
    return '';
  } else if (typeof message === 'string') {
    return message;
  } else {
    return JSON.stringify(message);
  }
}

function formatPrintf(): Logform.Format {
  return format.printf(line => {
    const { timestamp, label, level, message, extra } = parseLogItem(line);

    const jsonMessage = toString(message);
    const jsonExtra = extra ? `: ${toString(extra)}` : '';
    return `${timestamp} [${label}] ${level} - ${jsonMessage}${jsonExtra}`;
  });
}

function formatJSON(): Logform.Format {
  return format.printf(line => {
    return JSON.stringify(parseLogItem(line));
  });
}

function getLogFormat(label: string) {
  const combineProd = [
    format.label({ label }),
    format.timestamp(),
    format.json(),
    formatJSON(),
  ];

  const combineDev = [
    format.label({ label }),
    format.timestamp(),
    formatPrintf(),
    format.colorize({ all: true }),
  ];

  return env.isDevelopment
    ? format.combine(...combineDev)
    : format.combine(...combineProd);
}

function getOptions(label: string): LoggerOptions {
  const level = env.isDevelopment ? 'debug' : 'info';
  const logFormat = getLogFormat(label);
  return {
    level,
    format: logFormat,
    transports: [
      new transports.Console()
    ],
  };
}

function createLogger(label: string): Logger {
  const options = getOptions(label);
  return winston.createLogger(options);
}


export default createLogger;
```
