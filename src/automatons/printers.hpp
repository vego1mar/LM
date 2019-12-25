#ifndef PRINTERS_HPP
#define PRINTERS_HPP

#include "definitions.hpp"

namespace automatons {

    class IAutomataPrinter {
    protected:
        bool verbosity = true;

    public:
        IAutomataPrinter() = default;

        IAutomataPrinter(const IAutomataPrinter &rhs) = delete;

        IAutomataPrinter(IAutomataPrinter &&rvalue) noexcept = delete;

        IAutomataPrinter &operator=(const IAutomataPrinter &rhs) = delete;

        IAutomataPrinter &operator=(IAutomataPrinter &&rvalue) noexcept = delete;

        virtual ~IAutomataPrinter() = default;

        void setVerbosity(bool verbose);

    };

    class NFAPrinter : public IAutomataPrinter {
    public:
        NFAPrinter() = default;

        NFAPrinter(const NFAPrinter &rhs) = delete;

        NFAPrinter(NFAPrinter &&rvalue) noexcept = delete;

        NFAPrinter &operator=(const NFAPrinter &rhs) = delete;

        NFAPrinter &operator=(NFAPrinter &&rvalue) noexcept = delete;

        ~NFAPrinter() override = default;

        void printTransition(const StateEventPair &previous, const States &next, int level) const;

        void printDerivationResult(bool isAcceptingState, bool wasTransitionDefined) const;

        void printNewLine() const;

    };

}

#endif //PRINTERS_HPP
