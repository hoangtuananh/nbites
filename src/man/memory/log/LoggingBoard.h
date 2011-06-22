/**
 *
 * @LoggingBoard - a class that will handle all of the logging objects for each
 * of the memory object
 * e.g. MVision can have a ZeroCopyFileLogger, whereas
 * MSensors can have a CodedFileLogger
 *
 * Also each logger depends on a FDProvider (that is a file descriptor
 * provider) to provide the file descriptor necessary. Some stuff
 * might go to a file, some might go to wifi, etc.
 *
 * @author Octavian Neamtu
 */

#pragma once

#include <map>
#include <string>

#include "include/io/FileFDProvider.h"

#include "CodedFileLogger.h"
#include "ImageFDLogger.h"
#include "memory/MObject.h"

//forward declaration
namespace man {
namespace memory {
namespace log {
class LoggingBoard;
}
}
}

#include "memory/Memory.h"

namespace man {
namespace memory {
namespace log {

typedef std::pair< const MObject*, FDLogger*> ObjectLoggerPair;
typedef std::pair< const MObject*, FDProvider*> ObjectFDProviderPair;

typedef std::map< const MObject*, FDLogger*> ObjectLoggerMap;
typedef std::map< const MObject*, FDProvider*> ObjectFDProviderMap;

class LoggingBoard {

public:
    LoggingBoard(const Memory* _memory);
    ~LoggingBoard();

    static LoggingBoard* NullLoggingBoard();

    void log(const MObject* mobject);

    const ImageFDLogger* getImageLogger(const MImage* mimage) const;
    const FDLogger* getLogger(const MObject* mobject) const;

protected:
    LoggingBoard();

private:
    void initLoggingObjects();

public:
    static const std::string MVISION_PATH;
    static const std::string MVISION_SENSORS_PATH;
    static const std::string MMOTION_SENSORS_PATH;
    static const std::string MIMAGE_PATH;

private:
    const Memory* memory;
    ObjectLoggerMap objectLoggerMap;
    ObjectFDProviderMap objectFDProviderMap;

};
}
}
}
