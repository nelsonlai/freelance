import chalk from 'chalk';

export enum LogLevel {
  DEBUG = 0,
  INFO = 1,
  WARN = 2,
  ERROR = 3,
}

class Logger {
  private level: LogLevel;

  constructor(level: LogLevel = LogLevel.INFO) {
    this.level = level;
  }

  private formatTimestamp(): string {
    return new Date().toISOString();
  }

  private log(level: LogLevel, color: chalk.ChalkFunction, message: string, data?: any) {
    if (level >= this.level) {
      const timestamp = this.formatTimestamp();
      const levelName = LogLevel[level];
      
      console.log(
        `${chalk.gray(timestamp)} ${color(`[${levelName}]`)} ${message}`
      );
      
      if (data) {
        if (typeof data === 'object') {
          console.log(chalk.gray(JSON.stringify(data, null, 2)));
        } else {
          console.log(chalk.gray(data));
        }
      }
    }
  }

  debug(message: string, data?: any) {
    this.log(LogLevel.DEBUG, chalk.blue, message, data);
  }

  info(message: string, data?: any) {
    this.log(LogLevel.INFO, chalk.green, message, data);
  }

  warn(message: string, data?: any) {
    this.log(LogLevel.WARN, chalk.yellow, message, data);
  }

  error(message: string, data?: any) {
    this.log(LogLevel.ERROR, chalk.red, message, data);
  }

  // Special methods for HTTP requests
  request(method: string, url: string, ip?: string) {
    this.info(`📥 ${method} ${url}`, ip ? { ip } : undefined);
  }

  response(method: string, url: string, statusCode: number, responseTime?: number) {
    const color = statusCode >= 400 ? chalk.red : statusCode >= 300 ? chalk.yellow : chalk.green;
    const emoji = statusCode >= 400 ? '❌' : statusCode >= 300 ? '⚠️' : '✅';
    this.info(`${emoji} ${method} ${url} - ${color(statusCode)}`, responseTime ? { responseTime: `${responseTime}ms` } : undefined);
  }

  // Database operations
  db(operation: string, table: string, data?: any) {
    this.debug(`🗄️  DB ${operation} on ${table}`, data);
  }

  // Security events
  security(event: string, details?: any) {
    this.warn(`🔒 Security: ${event}`, details);
  }
}

// Create default logger instance
export const logger = new Logger(
  (process.env.LOG_LEVEL as unknown as LogLevel) || LogLevel.INFO
);

export default logger;
