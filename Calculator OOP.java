import java.util.ArrayList;
import java.util.Scanner;

/**
 * Class Main where all the operations are executed.
 *
 * @author timurzeksimbaev
 * @version 1
 */
public class Assignment3 {
    /**
     * Field scanner for scanning from console.
     */
    private final Scanner SCANNER = new Scanner(System.in);
    /**
     * Function which executes the program.
     * @param args
     */
    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<String>();
        Assignment3 main = new Assignment3();
        Calculator calculator = new IntegerCalculator();
        CalculatorType calcType = main.readCalculator();
        switch (calcType) {
            case INTEGER:
                calculator = new IntegerCalculator();
                break;
            case DOUBLE:
                calculator = new DoubleCalculator();
                break;
            case STRING:
                calculator = new StringCalculator();
                break;
            default:
                main.reportFatalError("Wrong calculator type");
        }
        int n = main.readCommandsNumber();
        for (int i = 0; i < n; i++) {
            String str = main.SCANNER.nextLine();
            String[] word = str.split(" ");
            final int amountOfOperands = 3;
            if (word.length != amountOfOperands) {
                list.add("Wrong argument type");
                break;
            }
            OperationType opType = main.parseOperation(word[0]);
            switch (opType) {
                case ADDITION:
                    list.add(calculator.add(word[1], word[2]));
                    break;
                case SUBTRACTION:
                    list.add(calculator.subtract(word[1], word[2]));
                    break;
                case MULTIPLICATION:
                    list.add(calculator.multiply(word[1], word[2]));
                    break;
                case DIVISION:
                    list.add(calculator.divide(word[1], word[2]));
                    break;
                default:
                    list.add("Wrong operation type");
            }
        }
        for (int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }
    }
    /**
     * Method readCalculator, which scans calculator type.
     *
     * @return returns object of class CalculatorType
     */
    private CalculatorType readCalculator() {
        String calculatorName = SCANNER.nextLine();
        switch (calculatorName) {
            case "INTEGER":
                return CalculatorType.INTEGER;
            case "DOUBLE":
                return CalculatorType.DOUBLE;
            case "STRING":
                return CalculatorType.STRING;
            default:
                return CalculatorType.INCORRECT;
        }
    }
    /**
     * Method readCommandsNumber, which scans number of commands n.
     *
     * @return returns m - integer value of n
     */
    private int readCommandsNumber() {
        String n = SCANNER.nextLine();
        try {
            Integer.parseInt(n);
        } catch (NumberFormatException ex) {
            reportFatalError("Amount of commands is Not a Number");
        }
        final int maxLength = 50;
        final int minLength = 1;
        int m = Integer.parseInt(n);
        if (m > maxLength || m < minLength) {
            reportFatalError("Amount of commands is Not a Number");
        }
        return m;
    }
    /**
     * Method reportFatalError, which prints fatal errors, such as:
     * "Wrong calculator type", "Amount of commands is Not a Number".
     *
     * @param err string which will be printed
     */
    private void reportFatalError(String err) {
        System.out.println(err);
        System.exit(0);
    }
    /**
     * Method parseOperation, which helps to define operation type.
     * @param operation operation type
     * @return returns OperationType object
     */
    private OperationType parseOperation(String operation) {
        switch (operation) {
            case "+":
                return OperationType.ADDITION;
            case "-":
                return OperationType.SUBTRACTION;
            case "*":
                return OperationType.MULTIPLICATION;
            case "/":
                return OperationType.DIVISION;
            default:
                return OperationType.INCORRECT;
        }
    }
}
/**
 * Enum which contains four objects: INTEGER, DOUBLE, STRING, INCORRECT.
 */
enum CalculatorType {
    /** Integer calculator type. */
    INTEGER,
    /** Double calculator type. */
    DOUBLE,
    /** String calculator type. */
    STRING,
    /** Incorrect calculator type. */
    INCORRECT
}
/**
 * Enum which contains five objects: ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, INCORRECT.
 */
enum OperationType {
    /** Addition operation type. */
    ADDITION,
    /** Subtraction operation type. */
    SUBTRACTION,
    /** Multiplication operation type. */
    MULTIPLICATION,
    /** Division operation type. */
    DIVISION,
    /** Incorrect operation type. */
    INCORRECT
}

/**
 * Abstract class Calculator which has four abstract methods.
 * add to perform addition
 * subtract to perform subtraction
 * multiply to perform multiplication
 * divide to perform division
 */
abstract class Calculator {
    public abstract String add(String a, String b);
    public abstract String subtract(String a, String b);
    public abstract String multiply(String a, String b);
    public abstract String divide(String a, String b);
}

/**
 * Class IntegerCalculator - inheritor of class Calculator.
 * Has all methods of parent class
 * Used to perform operations with integers
 */
class IntegerCalculator extends Calculator {
    /**
     * Method to check if there are invalid inputs for integer calculator.
     * @param x - first string
     * @param y - second string
     * @return returns true if there are problems, otherwise false
     */
    private boolean intCheck(String x, String y) {
        try {
            Integer.parseInt(x);
            Integer.parseInt(y);
        } catch (NumberFormatException eInt) {
            return true;
        }
        return false;
    }
    /**
     * Method for adding two integer numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or addition of two integers
     */
    @Override
    public String add(String a, String b) {
        if (intCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Integer.toString(Integer.parseInt(a) + Integer.parseInt(b));
        }
    }

    /**
     * Method for subtracting two integer numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or subtraction of two integers
     */
    @Override
    public String subtract(String a, String b) {
        if (intCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Integer.toString(Integer.parseInt(a) - Integer.parseInt(b));
        }
    }

    /**
     * Method for multiplying two integer numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or multiplication of two integers
     */
    @Override
    public String multiply(String a, String b) {
        if (intCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Integer.toString(Integer.parseInt(a) * Integer.parseInt(b));
        }
    }

    /**
     * Method for dividing two integer numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or division of two integers
     */
    @Override
    public String divide(String a, String b) {
        if (intCheck(a, b)) {
            return "Wrong argument type";
        } else if (b.equals("0")) {
            return "Division by zero";
        } else {
            return Integer.toString(Integer.parseInt(a) / Integer.parseInt(b));
        }
    }
}

/**
 * Class DoubleCalculator - inheritor of class Calculator.
 * Has all methods of parent class
 * Used to perform operations with double numbers
 */
class DoubleCalculator extends Calculator {
    /**
     * Method to check if there are invalid inputs for double calculator.
     * @param x - first string
     * @param y - second string
     * @return returns true if there are problems, otherwise false
     */
    private boolean dblCheck(String x, String y)  {
        try {
            Double.parseDouble(x);
            Double.parseDouble(y);
        } catch (NumberFormatException eDouble) {
            return true;
        }
        return false;
    }
    /**
     * Method for adding two double numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or addition of two double numbers
     */
    @Override
    public String add(String a, String b) {
        if (dblCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Double.toString(Double.parseDouble(a) + Double.parseDouble(b));
        }
    }
    /**
     * Method for subtracting two double numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or subtraction of two double numbers
     */
    @Override
    public String subtract(String a, String b) {
        if (dblCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Double.toString(Double.parseDouble(a) - Double.parseDouble(b));
        }
    }

    /**
     * Method for multiplying two double numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or multiplication of two double numbers
     */
    @Override
    public String multiply(String a, String b) {
        if (dblCheck(a, b)) {
            return "Wrong argument type";
        } else {
            return Double.toString(Double.parseDouble(a) * Double.parseDouble(b));
        }
    }

    /**
     * Method for dividing two double numbers.
     *
     * @param a - first number
     * @param b - second number
     * @return returns "Wrong argument type" or division of two double numbers
     */
    @Override
    public String divide(String a, String b) {
        if (dblCheck(a, b)) {
            return "Wrong argument type";
        } else if (b.equals("0")) {
            return "Division by zero";
        } else {
            return Double.toString(Double.parseDouble(a) / Double.parseDouble(b));
        }
    }
}

/**
 * Class StringCalculator - inheritor of class Calculator.
 * Has all methods of parent class
 * Used to perform operations with strings
 */
class StringCalculator extends Calculator {
    /**
     * Method for concatenating two strings.
     *
     * @param a - first string
     * @param b - second string
     * @return returns concatenation of two strings
     */
    @Override
    public String add(String a, String b) {
        return a + b;
    }
    /**
     * Method for subtracting two strings.
     *
     * @param a - first string
     * @param b - second string
     * @return returns "Unsupported operation for strings", because we cannot subtract strings
     */
    @Override
    public String subtract(String a, String b) {
        return "Unsupported operation for strings";
    }
    /**
     * Method for multiplying two strings.
     *
     * @param a - first string
     * @param b - second string
     * @return returns concatenation of string a b times
     */
    @Override
    public String multiply(String a, String b) {
        if (!b.matches("[0-9]+") || b.equals("0") || b.contains("-")) {
            return "Wrong argument type";
        } else {
            String s = "";
            for (int i = 0; i < Integer.parseInt(b); i++) {
                s += a;
            }
            return s;
        }
    }
    /**
     * Method for dividing two strings.
     *
     * @param a - first string
     * @param b - second string
     * @return returns "Unsupported operation for strings", because we cannot divide two strings
     */
    @Override
    public String divide(String a, String b) {
        return "Unsupported operation for strings";
    }
}
