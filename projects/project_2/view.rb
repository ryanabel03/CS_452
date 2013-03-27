require_relative "presenter.rb"
java_import 'javax.swing.JFrame'
java_import 'javax.swing.JButton'
java_import 'javax.swing.JPanel'
java_import 'java.awt.FlowLayout'
java_import 'javax.swing.JLabel'
java_import 'java.awt.event.ActionListener'
java_import 'javax.imageio.ImageIO'
java_import 'java.awt.Image'
java_import 'java.io.File'

class ButtonListener 
  include ActionListener

  def initialize(presenter, label)
    @presenter = presenter
    @label = label
  end

  def actionPerformed(e)
    @presenter.next_line
    line = @presenter.current_line
    total_lines = @presenter.total_lines
    @label.setText "Line #{line} of #{total_lines}"
  end
end

class ImagePanel < JPanel

  def initialize
    file = java.io.File.new("graph.png")
    @image = ImageIO.read(file)
  end

  def paintComponent(g)
    super.paintComponent(g)
    g.drawImage(@image, 0, 0, null)
  end
end

class View

  def initialize
    @presenter = Presenter.new
    @frame = JFrame.new "Test"
    @panel = JPanel.new
    @image = ImagePanel.new

    @step_button = JButton.new "Step"
    @step_button.setVisible true

    setup_count_labels

    @step_button.addActionListener ButtonListener.new(@presenter, @count_label)

    @panel.add(@step_button)



    @frame.add(@panel)
    @frame.add(@image)

    @frame.setLayout(FlowLayout.new)
    @frame.setSize(400,400)
    @frame.setVisible(true)

  end

  def setup_count_labels
    line = @presenter.current_line
    total_lines = @presenter.total_lines
    @count_label = JLabel.new "Line #{line} of #{total_lines}"
    @count_label.setVisible(true)

    @panel.add(@count_label)
  end

end


View.new
