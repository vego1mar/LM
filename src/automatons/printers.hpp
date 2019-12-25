#ifndef PRINTERS_HPP
#define PRINTERS_HPP

#include "definitions.hpp"

namespace automatons {

    class IAutomataPrinter {
    private:
        bool verbosity = true;

    public:
        IAutomataPrinter() = default;

        IAutomataPrinter(const IAutomataPrinter &rhs) = delete;

        IAutomataPrinter(IAutomataPrinter &&rvalue) noexcept = delete;

        IAutomataPrinter &operator=(const IAutomataPrinter &rhs) = delete;

        IAutomataPrinter &operator=(IAutomataPrinter &&rvalue) noexcept = delete;

        virtual ~IAutomataPrinter() = default;

        void setVerbosity(bool verbose);

    protected:
        bool getVerbosity() const;

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

    class DFAPrinter : public IAutomataPrinter {
    public:
        DFAPrinter() = default;

        DFAPrinter(const DFAPrinter &rhs) = delete;

        DFAPrinter(DFAPrinter &&rvalue) = delete;

        DFAPrinter &operator=(const DFAPrinter &rhs) = delete;

        DFAPrinter &operator=(DFAPrinter &&rvalue) = delete;

        ~DFAPrinter() override = default;

        void printTransition(const StateEventPair &currentPair, const int &nextState) const;

        void printDerivationResult(bool isAcceptingState) const;

    };

}

#endif //PRINTERS_HPP
