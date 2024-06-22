package sudokuSolver;

import javax.swing.JPanel;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;

class ButtonActionListener implements ActionListener {
    private JButton mainButton;
    private int[][] sudoku;
    private JButton[][] buttons;

    public ButtonActionListener(JButton mainButton, int[][] sudoku, JButton[][] buttons) {
        this.mainButton = mainButton;
        this.sudoku = sudoku;
        this.buttons = buttons;
    }

    public void actionPerformed(ActionEvent e) {
        JPanel panel = new JPanel(new GridLayout(3, 3));
        JDialog dialog = new JDialog();
        dialog.setModal(true);
        dialog.setTitle("Select a number");

        for (int i = 1; i <= 10; i++) {
            JButton button;
            if (i != 10) {
                button = new JButton(String.valueOf(i));
                button.setBackground(Color.WHITE);
                button.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        mainButton.setText(button.getText());
                        String[] indices = mainButton.getName().split(",");
                        int row = Integer.parseInt(indices[0]);
                        int col = Integer.parseInt(indices[1]);
                        sudoku[row][col] = Integer.parseInt(button.getText());
                        dialog.dispose();
                    }
                });
            } else {
                button = new JButton();
                button.setBackground(Color.WHITE);
                button.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        mainButton.setText(button.getText());
                        String[] indices = mainButton.getName().split(",");
                        int row = Integer.parseInt(indices[0]);
                        int col = Integer.parseInt(indices[1]);
                        sudoku[row][col] = 0;
                        dialog.dispose();
                    }
                });
            }
            panel.add(button);
        }

        dialog.add(panel);
        dialog.pack();
        dialog.setLocationRelativeTo(mainButton);
        dialog.setVisible(true);
    }
}
