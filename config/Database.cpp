#include "config/Database.hpp"
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>

namespace Adastra
{
    DatabaseException::DatabaseException(const std::string &message) : message(message) {}

    const char *DatabaseException::what() const noexcept
    {
        return message.c_str();
    }

    std::unique_ptr<Database> Database::instance = nullptr;
    std::mutex Database::mtx;

    Database::Database(const std::string &host, const std::string &user, const std::string &password, const std::string &database)
        : host(host), user(user), password(password), database(database)
    {
        connect();
    }

    void Database::connect()
    {
        try
        {
            if (!connection)
            {
                sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
                connection = std::shared_ptr<sql::Connection>(driver->connect(host, user, password));
                connection->setSchema(database);
                std::cout << "Connexion à la base de données réussie !" << std::endl;
            }
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur de connexion à la base de données : " + std::string(e.what()));
        }
    }

    std::unique_ptr<sql::ResultSet> Database::executeQuery(const std::string &query)
    {
        try
        {
            std::unique_ptr<sql::Statement> stmt(connection->createStatement());
            return std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête : " + std::string(e.what()));
        }
    }

    std::unique_ptr<sql::ResultSet> Database::executePreparedQuery(const std::string &query, int param)
    {
        try
        {
            std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
            pstmt->setInt(1, param);
            return std::unique_ptr<sql::ResultSet>(pstmt->executeQuery());
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête préparée : " + std::string(e.what()));
        }
    }

    std::shared_ptr<sql::Connection> Database::getConnection()
    {
        return connection;
    }

    Database::~Database()
    {
        std::cout << "Connexion à la base de données fermée." << std::endl;
    }

    std::unique_ptr<Database> &Database::getInstance(const std::string &host, const std::string &user, const std::string &password, const std::string &database)
    {
        if (!instance)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance)
            {
                instance = std::make_unique<Database>(host, user, password, database);
            }
        }
        return instance;
    }

    std::string Database::join(const std::vector<std::string> &vec, const std::string &delimiter)
    {
        std::string result;
        for (size_t i = 0; i < vec.size(); ++i)
        {
            result += vec[i];
            if (i != vec.size() - 1)
                result += delimiter;
        }
        return result;
    }

    std::string Database::placeholders(size_t count)
    {
        std::string ph;
        for (size_t i = 0; i < count; ++i)
        {
            if (i > 0)
                ph += ", ";
            ph += "?";
        }
        return ph;
    }

    std::string Database::createSetClause(const std::vector<std::string> &columns)
    {
        std::string setClause;
        for (const auto &col : columns)
        {
            if (!setClause.empty())
                setClause += ", ";
            setClause += col + " = ?";
        }
        return setClause;
    }

} // namespace Adastra

