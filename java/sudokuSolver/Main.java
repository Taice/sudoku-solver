package sudokuSolver;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main {

    public static void main(String[] args) {
        int[][] sudoku = new int[9][9];

        Window frame = new Window("Sudoku Solver", 600, 600);
        JPanel panel = new JPanel();
        frame.setContentPane(panel);

        frame.setLayout(new BorderLayout());

        JPanel outerPanel = new JPanel();
        outerPanel.setPreferredSize(new Dimension(400, 400));
        outerPanel.setLayout(new BorderLayout());

        JPanel topPanel = new JPanel(new GridLayout(3, 3));

        JButton[][] buttons = new JButton[9][9];

        for (int i = 0; i < 9; i++) {
            JPanel subPanel = new JPanel(new GridLayout(3, 3));
            subPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));

            for (int j = 0; j < 9; j++) {
                JButton button;
                if (sudoku[i][j] == 0) {
                    button = new JButton();
                } else {
                    button = new JButton(String.valueOf(sudoku[i][j]));
                }
                button.setName(i + "," + j);
                button.setPreferredSize(new Dimension(50, 50));
                button.setBorder(BorderFactory.createLineBorder(Color.GRAY, 1));
                button.setBackground(Color.WHITE);
                buttons[i][j] = button;
                subPanel.add(button);
                button.addActionListener(new ButtonActionListener(button, sudoku, buttons));
            }

            topPanel.add(subPanel);
        }

        JButton solveButton = new JButton("Solve");
        solveButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Sudoku solver = new Sudoku(sudoku);
                if (solver.solve()) {
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            buttons[i][j].setText(String.valueOf(sudoku[i][j]));
                        }
                    }
                } else {
                    JOptionPane.showMessageDialog(frame, "No solution exists!");
                }
            }
        });

        outerPanel.add(topPanel, BorderLayout.CENTER);
        frame.add(outerPanel, BorderLayout.CENTER);
        frame.add(solveButton, BorderLayout.SOUTH);
        frame.setVisible(true);

    }

}
