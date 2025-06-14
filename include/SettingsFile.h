#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#include <string>

/**
 * @brief This class is an interface for a settings file.
 * It allows reading and writing to a settings file.
 * The user of this library must implement this class to use the settings storage.
 * It represents a specific file in the file system. To allow the system to select a specific file, the implementation
 * may use a constructor with a filename in it.
 */
class SettingsFile
{
public:
    using SettingsFileResult = enum { EndOfFile = -1, Success = 0, InvalidState, IOError };
    using FileStatus         = enum { FileClosed = 0, FileOpenedForRead, FileOpenedForWrite };

    /**
     * @brief Open the file for reading.
     * @return SettingsFileResult The result of the operation.
     * @retval Success The file was successfully opened.
     * @retval InvalidState The file is already open.
     */
    [[nodiscard]] virtual SettingsFileResult openForRead() = 0;

    /**
     * @brief Read a byte from the file.
     * @param byte The byte read from the file.
     * @return SettingsFileResult The result of the operation.
     * @retval EndOfFile The end of the file was reached.
     * @retval Success The byte was successfully read.
     * @retval InvalidState The file is not open.
     * @retval IOError An error occurred while reading the file.
     */
    [[nodiscard]] virtual SettingsFileResult read(char* byte) = 0;

    /**
     * @brief Read a line from the file. (Including the newline character '\n')
     * @param buffer The buffer to store the line read from the file.
     * @return SettingsFileResult The result of the operation.
     * @retval EndOfFile The end of the file was reached, and all the remaining data is stored in the buffer.
     * @retval Success The line was successfully read.
     * @retval InvalidState The file is not open.
     * @retval IOError An error occurred while reading the file.
     */
    [[nodiscard]] virtual SettingsFileResult readLine(std::string& buffer) = 0;

    /**
     * @brief Open the file for writing.
     * @return SettingsFileResult The result of the operation.
     * @retval Success The file was successfully opened.
     * @retval InvalidState The file is already open.
     */
    [[nodiscard]] virtual SettingsFileResult openForWrite() = 0;

    /**
     * @brief Write a byte to the file.
     *
     * The actual writing to the file does not need to happen immediately,
     * so delayed writing mechanisms can be implemented.
     * The implementation must guarantee that the changes are saved to the file at least
     * before opening for read again, if forceClose is called or if the destructor is called.
     *
     * @param byte The byte to write to the file.
     * @return SettingsFileResult The result of the operation.
     * @retval Success The byte was successfully written.
     * @retval InvalidState The file is not open.
     * @retval IOError An error occurred while writing the file.
     */
    [[nodiscard]] virtual SettingsFileResult write(char byte) = 0;

    /**
     * @brief Write a buffer to the file.
     *
     * The actual writing to the file does not need to happen immediately,
     * so delayed writing mechanisms can be implemented.
     * The implementation must guarantee that the changes are saved to the file at least
     * before opening for read again, if forceClose is called or if the destructor is called.
     *
     * @param data The buffer to write to the file.
     * @return SettingsFileResult The result of the operation.
     * @retval Success The buffer was successfully written.
     * @retval InvalidState The file is not open.
     * @retval IOError An error occurred while writing the file.
     */
    [[nodiscard]] virtual SettingsFileResult write(const std::string& data) = 0;

    /**
     * @brief Close the file.
     * @return SettingsFileResult The result of the operation.
     * @retval Success The file was successfully closed.
     * @retval InvalidState The file is not open.
     */
    virtual SettingsFileResult close() = 0;

    /**
     * @brief Get the open state of the file.
     * @return FileStatus The open state of the file.
     */
    [[nodiscard]] virtual FileStatus getOpenStatus() = 0;

    /**
     * @brief Write to disk any pending data and close the file if opened.
     * The main difference between close and forceClose is that this function is used
     * to signal the SettingsFile implementation that the File must be closed and written to disk immediately.
     * Whereas in the close function,
     * it was possible for some implementations to delay the writing to disk reducing write cicles in some cases.
     */
    virtual void forceClose() = 0;

    virtual ~SettingsFile() = default;
};

#endif // SETTINGSFILE_H
