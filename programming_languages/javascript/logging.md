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
  stack: string,
  extra: unknown,
};

function parseLogItem(line: Logform.TransformableInfo): LogItem {
  const { timestamp, label, level, stack } = line;
  let { message } = line;
  const splat = line[Symbol.for('splat')] || [];
  if (splat.length > 1) {
    throw new Error('logger only accepts 1 extra object but provided: '
      + `${splat.length}, please wrap them in the same object`);
  }
  const extra = splat[0];
  if (extra?.hasOwnProperty('message')) {
    message = message.replace(' ' + extra.message, '');
  }
  return { timestamp, label, level, message, stack, extra };
}

function jsonReplacer(_: string, value: unknown) {
  if (!value) {
    return '';
  } else if (value instanceof Error) {
    return value.stack;
  } else if (typeof value !== 'object') {
    return value.toString();
  } else {
    return value;
  }
}

interface MessageObject {
  message?: string;
}

function toString(obj: MessageObject | string) {
  if (typeof obj === 'string') {
    return obj;
  } else if (obj.hasOwnProperty('message')) {
    return obj.message;
  } else if (env.isDevelopment) {
    return JSON.stringify(obj, jsonReplacer, 2);
  } else {
    return JSON.stringify(obj, jsonReplacer);
  }
}

function formatPrintf(): Logform.Format {
  return format.printf(line => {
    const {
      timestamp, label, level, message, stack, extra
    } = parseLogItem(line);
    const msgStr = toString(message);
    const extraStr = extra ? `: ${toString(extra)}` : '';
    const stackStr = stack ? `\n${toString(stack)}` : '';
    return `${timestamp} [${label}] ${level} - ${msgStr}${extraStr}${stackStr}`;
  });
}

function formatJSON(): Logform.Format {
  return format.printf(line => {
    const logItem = parseLogItem(line);
    // Prevent duplicated output of error
    if (logItem.extra instanceof Error) {
      delete logItem.extra;
    }
    return JSON.stringify(logItem, jsonReplacer);
  });
}

function getLogFormat(label: string) {
  const combineProd = [
    format.label({ label }),
    format.timestamp(),
    format.errors({ stack: true }),
    format.json(),
    formatJSON(),
  ];

  const combineDev = [
    format.label({ label }),
    format.timestamp(),
    format.errors({ stack: true }),
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
