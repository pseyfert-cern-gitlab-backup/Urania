/**
 * @file NamedLogger.h - nice logging for classes with names
 *
 * @author Manuel Schiller
 * @date 2008-12-11
 */
#ifndef NAMEDLOGGER_H
#define NAMEDLOGGER_H

#include <string>
#include <iostream>
#include "logstream.h"

/// base class to define per class logging streams
/** classes wishing to do per-instance logging should inherit from this
 * class
 */
class NamedLogger
{
  protected:
    /// default constructor (without a name, we use the standard streams)
    NamedLogger() :
      debug( logstreams::debug),
      warn(  logstreams::warn),
      info(  logstreams::info),
      error( logstreams::error),
      fatal( logstreams::fatal),
      always(logstreams::always)
  { logstreams::logstream::setMaxNameWidth(32); }
    /// constructor
    NamedLogger(const std::string& name) :
      debug( logstreams::logstream::get(std::cerr, 0, "DEBUG   " + name)),
      warn(  logstreams::logstream::get(std::cerr, 1, "WARNING " + name)),
      info(  logstreams::logstream::get(std::cerr, 2, "INFO    " + name)),
      error( logstreams::logstream::get(std::cerr, 3, "ERROR   " + name)),
      fatal( logstreams::logstream::get(std::cerr, 4, "FATAL   " + name)),
      always(logstreams::logstream::get(std::cerr, 5, "ALWAYS  " + name))
  { logstreams::logstream::setMaxNameWidth(32); }
    /// copy constructor
    NamedLogger(const NamedLogger& other) :
      debug( other.debug.clone()),
      warn(  other.warn.clone()),
      info(  other.info.clone()),
      error( other.error.clone()),
      fatal( other.fatal.clone()),
      always(other.always.clone())
  { }
    /// destructor
    virtual ~NamedLogger()
    {
      debug.release();
      warn.release();
      info.release();
      error.release();
      fatal.release();
      always.release();
    }

    logstreams::logstream& debug;	///< per-class debug stream
    logstreams::logstream& warn;	///< per-class warning stream
    logstreams::logstream& info;	///< per-class info stream
    logstreams::logstream& error;	///< per-class error stream
    logstreams::logstream& fatal;	///< per-class fatal stream
    logstreams::logstream& always;	///< per-class always stream
};

#endif // NAMEDLOGGER_H

// vim:sw=4:tw=78:ft=cpp
